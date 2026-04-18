#include "AlsTopDownPlayerController.h"

#include "AlsTopDownCharacter.h"
#include "AlsTopDownInputConfig.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "HAL/IConsoleManager.h"
#include "InputMappingContext.h"
#include "InputActionValue.h"
#include "Kismet/KismetMathLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsTopDownPlayerController)

DEFINE_LOG_CATEGORY_STATIC(LogAlsTopDownNetDebug, Log, All);

namespace AlsTopDownNetDebug
{
	static TAutoConsoleVariable<int32> CVarEnable(
		TEXT("als.TopDown.NetDebug"),
		0,
		TEXT("Enable ALS TopDown client/server aim debug logging.\n0: Disabled\n1: Enabled"),
		ECVF_Default);
}

AAlsTopDownPlayerController::AAlsTopDownPlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	DefaultMouseCursor = EMouseCursor::Default;
}

void AAlsTopDownPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ApplyInputMappingContext(true);
}

void AAlsTopDownPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ApplyInputMappingContext(false);
	Super::EndPlay(EndPlayReason);
}

void AAlsTopDownPlayerController::PlayerTick(const float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	if (bUpdateFacingFromCursorEveryTick)
	{
		UpdateAimFromCursor();
	}
}

void AAlsTopDownPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	SetupTopDownInput();
}

UAlsTopDownInputConfig* AAlsTopDownPlayerController::GetTopDownInputConfig() const
{
	return InputConfig;
}

void AAlsTopDownPlayerController::BindDefaultTopDownInput()
{
	auto* EnhancedInput = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInput) || !IsValid(InputConfig))
	{
		return;
	}

	if (IsValid(InputConfig->MoveAction))
	{
		EnhancedInput->BindAction(InputConfig->MoveAction, ETriggerEvent::Triggered, this, &ThisClass::HandleMoveAction);
		EnhancedInput->BindAction(InputConfig->MoveAction, ETriggerEvent::Canceled, this, &ThisClass::HandleMoveAction);
	}

	if (IsValid(InputConfig->ZoomAction))
	{
		EnhancedInput->BindAction(InputConfig->ZoomAction, ETriggerEvent::Triggered, this, &ThisClass::HandleZoomAction);
	}
}

bool AAlsTopDownPlayerController::UpdateAimFromCursor()
{
	AAlsTopDownCharacter* TopDownCharacter = ResolveTopDownCharacter();
	if (!IsValid(TopDownCharacter))
	{
		return false;
	}

	float MouseScreenX = 0.0f;
	float MouseScreenY = 0.0f;
	if (!GetMousePosition(MouseScreenX, MouseScreenY))
	{
		return false;
	}

	const FVector2D CurrentMouseScreenPosition{MouseScreenX, MouseScreenY};
	const bool bCursorMovedEnough =
		!bHasProcessedCursorScreenPosition ||
		FVector2D::Distance(CurrentMouseScreenPosition, LastProcessedCursorScreenPosition) >= CursorScreenMoveThreshold;

	if (bOnlyUpdateAimWhenCursorMoves && !bCursorMovedEnough)
	{
		if (AlsTopDownNetDebug::CVarEnable.GetValueOnGameThread() != 0)
		{
			UE_LOG(
				LogAlsTopDownNetDebug,
				Warning,
				TEXT("[ClientAim] SkipByCursorStill Controller=%s Pawn=%s Cursor=(%.1f, %.1f) LastCursor=(%.1f, %.1f) Threshold=%.2f"),
				*GetName(),
				GetPawn() ? *GetPawn()->GetName() : TEXT("None"),
				CurrentMouseScreenPosition.X,
				CurrentMouseScreenPosition.Y,
				LastProcessedCursorScreenPosition.X,
				LastProcessedCursorScreenPosition.Y,
				CursorScreenMoveThreshold);
		}
		return false;
	}

	LastProcessedCursorScreenPosition = CurrentMouseScreenPosition;
	bHasProcessedCursorScreenPosition = true;

	FVector NewCursorWorldPoint;
	if (!QueryCursorWorldPoint(NewCursorWorldPoint))
	{
		return false;
	}

	CursorWorldPoint = NewCursorWorldPoint;

	if (!bHasSmoothedAimPoint)
	{
		SmoothedAimWorldPoint = CursorWorldPoint;
		bHasSmoothedAimPoint = true;
	}
	else if (bSmoothAimPoint && AimPointSmoothingSpeed > UE_SMALL_NUMBER)
	{
		const float DeltaTime = GetWorld() != nullptr ? GetWorld()->GetDeltaSeconds() : 0.0f;
		SmoothedAimWorldPoint = FMath::VInterpTo(SmoothedAimWorldPoint, CursorWorldPoint, DeltaTime, AimPointSmoothingSpeed);
	}
	else
	{
		SmoothedAimWorldPoint = CursorWorldPoint;
	}

	return ApplyAimYaw(TopDownCharacter->CalculateTopDownAimYaw(SmoothedAimWorldPoint));
}

bool AAlsTopDownPlayerController::QueryCursorWorldPoint(FVector& OutWorldPoint) const
{
	if (AimPointMode == EAlsTopDownAimPointMode::GroundPlane)
	{
		return QueryGroundPlaneAimPoint(OutWorldPoint);
	}

	FHitResult HitResult;
	const ETraceTypeQuery TraceType = UEngineTypes::ConvertToTraceType(CursorTraceChannel.GetValue());
	if (GetHitResultUnderCursorByChannel(TraceType, true, HitResult) && HitResult.bBlockingHit)
	{
		OutWorldPoint = HitResult.ImpactPoint;
		return true;
	}

	FVector WorldOrigin;
	FVector WorldDirection;
	if (!DeprojectMousePositionToWorld(WorldOrigin, WorldDirection))
	{
		return false;
	}

	const APawn* ControlledPawn = GetPawn();
	const FVector PlaneOrigin = IsValid(ControlledPawn) ? ControlledPawn->GetActorLocation() : FVector::ZeroVector;
	const FPlane GroundPlane{PlaneOrigin, FVector::UpVector};

	float PlaneDistance = 0.0f;
	FVector PlaneIntersection = FVector::ZeroVector;
	if (!UKismetMathLibrary::LinePlaneIntersection(
		WorldOrigin,
		WorldOrigin + WorldDirection * 500000.0f,
		GroundPlane,
		PlaneDistance,
		PlaneIntersection))
	{
		return false;
	}

	OutWorldPoint = PlaneIntersection;
	return true;
}

void AAlsTopDownPlayerController::ApplyInputMappingContext(const bool bAddMappingContext)
{
	if (!bAutoManageInputMappingContext || !IsLocalController() || !IsValid(InputConfig))
	{
		return;
	}

	UInputMappingContext* MappingContext = InputConfig->InputMappingContext.Get();
	if (!IsValid(MappingContext))
	{
		return;
	}

	ULocalPlayer* LocalPlayer = GetLocalPlayer();
	if (!IsValid(LocalPlayer))
	{
		return;
	}

	auto* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	if (!IsValid(InputSubsystem))
	{
		return;
	}

	if (bAddMappingContext)
	{
		FModifyContextOptions Options;
		Options.bNotifyUserSettings = true;
		InputSubsystem->AddMappingContext(MappingContext, 0, Options);
		return;
	}

	InputSubsystem->RemoveMappingContext(MappingContext);
}

void AAlsTopDownPlayerController::HandleMoveAction(const FInputActionValue& ActionValue)
{
	if (AAlsTopDownCharacter* TopDownCharacter = ResolveTopDownCharacter())
	{
		TopDownCharacter->ApplyTopDownMoveInput(ActionValue.Get<FVector2D>());
	}
}

void AAlsTopDownPlayerController::HandleZoomAction(const FInputActionValue& ActionValue)
{
	if (AAlsTopDownCharacter* TopDownCharacter = ResolveTopDownCharacter())
	{
		TopDownCharacter->ApplyTopDownZoomInput(ActionValue.Get<float>());
	}
}

AAlsTopDownCharacter* AAlsTopDownPlayerController::ResolveTopDownCharacter() const
{
	return Cast<AAlsTopDownCharacter>(GetPawn());
}

bool AAlsTopDownPlayerController::ApplyAimYaw(const float NewYaw)
{
	const FRotator CurrentControlRotation = GetControlRotation();
	const float DeltaYaw = FMath::FindDeltaAngleDegrees(CurrentControlRotation.Yaw, NewYaw);
	const bool bDebugEnabled = AlsTopDownNetDebug::CVarEnable.GetValueOnGameThread() != 0;
	if (FMath::Abs(DeltaYaw) < FMath::Max(0.0f, AimYawUpdateThreshold))
	{
		if (bDebugEnabled)
		{
			UE_LOG(
				LogAlsTopDownNetDebug,
				Warning,
				TEXT("[ClientAim] SkipByThreshold Controller=%s Pawn=%s CurrentYaw=%.2f NewYaw=%.2f DeltaYaw=%.4f Threshold=%.4f AimPoint=(%.1f, %.1f, %.1f)"),
				*GetName(),
				GetPawn() ? *GetPawn()->GetName() : TEXT("None"),
				CurrentControlRotation.Yaw,
				NewYaw,
				DeltaYaw,
				AimYawUpdateThreshold,
				SmoothedAimWorldPoint.X,
				SmoothedAimWorldPoint.Y,
				SmoothedAimWorldPoint.Z);
		}
		return false;
	}

	const float CurrentTime = GetWorld() != nullptr ? static_cast<float>(GetWorld()->GetTimeSeconds()) : 0.0f;
	if (bLimitAimUpdateRate && LastAimUpdateTime > 0.0f && CurrentTime - LastAimUpdateTime < MinAimUpdateInterval)
	{
		if (bDebugEnabled)
		{
			UE_LOG(
				LogAlsTopDownNetDebug,
				Warning,
				TEXT("[ClientAim] SkipByRateLimit Controller=%s Pawn=%s CurrentYaw=%.2f NewYaw=%.2f DeltaYaw=%.4f DeltaTime=%.4f MinInterval=%.4f"),
				*GetName(),
				GetPawn() ? *GetPawn()->GetName() : TEXT("None"),
				CurrentControlRotation.Yaw,
				NewYaw,
				DeltaYaw,
				CurrentTime - LastAimUpdateTime,
				MinAimUpdateInterval);
		}
		return false;
	}

	SetControlRotation(FRotator{0.0f, FMath::UnwindDegrees(NewYaw), 0.0f});
	LastAppliedAimYaw = FMath::UnwindDegrees(NewYaw);
	LastAimUpdateTime = CurrentTime;

	// 同时更新角色的 TopDown 朝向
	if (AAlsTopDownCharacter* TopDownCharacter = ResolveTopDownCharacter())
	{
		TopDownCharacter->SetTopDownFacingYaw(NewYaw);
	}

	if (bDebugEnabled)
	{
		UE_LOG(
			LogAlsTopDownNetDebug,
			Warning,
			TEXT("[ClientAim] Applied Controller=%s Pawn=%s CurrentYaw=%.2f NewYaw=%.2f DeltaYaw=%.4f Time=%.4f AimPoint=(%.1f, %.1f, %.1f) RawPoint=(%.1f, %.1f, %.1f)"),
			*GetName(),
			GetPawn() ? *GetPawn()->GetName() : TEXT("None"),
			CurrentControlRotation.Yaw,
			LastAppliedAimYaw,
			DeltaYaw,
			CurrentTime,
			SmoothedAimWorldPoint.X,
			SmoothedAimWorldPoint.Y,
			SmoothedAimWorldPoint.Z,
			CursorWorldPoint.X,
			CursorWorldPoint.Y,
			CursorWorldPoint.Z);
	}
	return true;
}

bool AAlsTopDownPlayerController::QueryGroundPlaneAimPoint(FVector& OutWorldPoint) const
{
	FVector WorldOrigin;
	FVector WorldDirection;
	if (!DeprojectMousePositionToWorld(WorldOrigin, WorldDirection))
	{
		return false;
	}

	const APawn* ControlledPawn = GetPawn();
	const FVector PlaneOrigin = IsValid(ControlledPawn) ? ControlledPawn->GetActorLocation() : FVector::ZeroVector;
	const FPlane GroundPlane{PlaneOrigin, FVector::UpVector};

	float PlaneDistance = 0.0f;
	FVector PlaneIntersection = FVector::ZeroVector;
	if (!UKismetMathLibrary::LinePlaneIntersection(
		WorldOrigin,
		WorldOrigin + WorldDirection * 500000.0f,
		GroundPlane,
		PlaneDistance,
		PlaneIntersection))
	{
		return false;
	}

	OutWorldPoint = PlaneIntersection;
	return true;
}
