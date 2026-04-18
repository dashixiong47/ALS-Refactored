#include "AlsTopDownCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsTopDownCharacter)

AAlsTopDownCharacter::AAlsTopDownCharacter()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName{TEXTVIEW("SpringArm")});
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = TargetZoom;
	SpringArm->SetRelativeRotation_Direct(FRotator{CameraPitch, CameraYaw, 0.0f});
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->bDoCollisionTest = true;
	SpringArm->SetUsingAbsoluteLocation(true);
	SpringArm->SetUsingAbsoluteRotation(true);

	Camera = CreateDefaultSubobject<UCameraComponent>(FName{TEXTVIEW("TopDownCamera")});
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	bUseTopDownFacing = true;
	bUseControllerRotationYaw = false;
	bDesiredAiming = true;

	if (auto* CharacterMovementComponent{GetCharacterMovement()})
	{
		CharacterMovementComponent->bOrientRotationToMovement = false;
	}

	DesiredRotationMode = AlsRotationModeTags::Aiming;
	TargetZoom = SpringArm->TargetArmLength;
}

void AAlsTopDownCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateCameraAnchor(DeltaTime);
	UpdateCameraZoom(DeltaTime);
	ApplyCameraAnchorTransform();
}

void AAlsTopDownCharacter::CalcCamera(const float DeltaTime, FMinimalViewInfo& ViewInfo)
{
	if (Camera->IsActive())
	{
		Camera->GetCameraView(DeltaTime, ViewInfo);
		return;
	}

	Super::CalcCamera(DeltaTime, ViewInfo);
}

void AAlsTopDownCharacter::ApplyTopDownMoveInput(const FVector2D InputValue)
{
	if (!Controller || InputValue.IsNearlyZero())
	{
		return;
	}

	const FVector CameraForwardPlanar = FVector::VectorPlaneProject(Camera->GetForwardVector(), FVector::UpVector).GetSafeNormal();
	const FVector CameraRightPlanar = FVector::VectorPlaneProject(Camera->GetRightVector(), FVector::UpVector).GetSafeNormal();

	AddMovementInput(CameraForwardPlanar, InputValue.Y);
	AddMovementInput(CameraRightPlanar, InputValue.X);
}

void AAlsTopDownCharacter::ApplyTopDownZoomInput(const float InputValue)
{
	if (FMath::IsNearlyZero(InputValue))
	{
		return;
	}

	TargetZoom = FMath::Clamp(TargetZoom - InputValue * ZoomStep, ZoomMin, ZoomMax);
}

float AAlsTopDownCharacter::CalculateTopDownAimYaw(const FVector& WorldTarget) const
{
	const FVector Direction = WorldTarget - GetActorLocation();
	if (Direction.SizeSquared2D() <= UE_SMALL_NUMBER)
	{
		return CachedFacingYaw;
	}

	const float NewYaw = FMath::RadiansToDegrees(FMath::Atan2(Direction.Y, Direction.X));
	return FMath::UnwindDegrees(NewYaw);
}

void AAlsTopDownCharacter::UpdateCameraAnchor(const float DeltaTime)
{
	const FVector ActorLocation = GetActorLocation();

	if (!bCameraAnchorInitialized)
	{
		CameraAnchorLocation = ActorLocation;
		CameraAnchorTargetLocation = ActorLocation;
		bCameraAnchorInitialized = true;
		return;
	}

	if (!IsLocallyControlled())
	{
		CameraAnchorLocation = ActorLocation;
		CameraAnchorTargetLocation = ActorLocation;
		CameraRecenteringTimer = 0.0f;
		bIsCameraRecentering = false;
		bIsOutsideCameraDeadZone = false;
		return;
	}

	if (!bEnableScreenDeadZoneFollow)
	{
		CameraAnchorLocation = ActorLocation;
		CameraAnchorTargetLocation = ActorLocation;
		CameraRecenteringTimer = 0.0f;
		bIsCameraRecentering = false;
		bIsOutsideCameraDeadZone = false;
		return;
	}

	FVector DesiredAnchor = CameraAnchorLocation;
	bool bShouldRecenter = false;
	const bool bHasDesiredAnchor = ResolveDeadZoneState(DeltaTime, DesiredAnchor, bShouldRecenter);
	if (!bHasDesiredAnchor)
	{
		DesiredAnchor = FVector{ActorLocation.X, ActorLocation.Y, ActorLocation.Z};
		bShouldRecenter = false;
		bIsOutsideCameraDeadZone = false;
		CameraRecenteringTimer = 0.0f;
	}

	DesiredAnchor.Z = ActorLocation.Z;
	CameraAnchorTargetLocation = DesiredAnchor;

	float InterpSpeed = DeadZoneFollowInterpSpeed;
	if (bShouldRecenter)
	{
		switch (RecenteringMode)
		{
		case EAlsTopDownCameraRecenteringMode::Smooth:
			InterpSpeed = SmoothRecenteringInterpSpeed;
			break;
		case EAlsTopDownCameraRecenteringMode::Fast:
			InterpSpeed = FastRecenteringInterpSpeed;
			break;
		default:
			break;
		}
	}

	if (InterpSpeed <= UE_SMALL_NUMBER)
	{
		CameraAnchorLocation = CameraAnchorTargetLocation;
		return;
	}

	CameraAnchorLocation = FMath::VInterpTo(CameraAnchorLocation, CameraAnchorTargetLocation, DeltaTime, InterpSpeed);
}

void AAlsTopDownCharacter::UpdateCameraZoom(const float DeltaTime)
{
	if (!IsValid(SpringArm))
	{
		return;
	}

	SpringArm->TargetArmLength = FMath::FInterpTo(SpringArm->TargetArmLength, TargetZoom, DeltaTime, ZoomInterpSpeed);
}

void AAlsTopDownCharacter::ApplyCameraAnchorTransform() const
{
	if (!IsValid(SpringArm))
	{
		return;
	}

	SpringArm->SetWorldLocation(CameraAnchorLocation);
	SpringArm->SetWorldRotation(FRotator{CameraPitch, CameraYaw, 0.0f});
}

bool AAlsTopDownCharacter::ResolveDeadZoneState(float DeltaTime, FVector& OutDesiredAnchor, bool& bOutShouldRecenter)
{
	bOutShouldRecenter = false;

	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!IsValid(PlayerController))
	{
		return false;
	}

	int32 ViewportSizeX = 0;
	int32 ViewportSizeY = 0;
	PlayerController->GetViewportSize(ViewportSizeX, ViewportSizeY);
	if (ViewportSizeX <= 0 || ViewportSizeY <= 0)
	{
		return false;
	}

	FVector2D ActorScreenPosition;
	if (!PlayerController->ProjectWorldLocationToScreen(GetActorLocation(), ActorScreenPosition, true))
	{
		return false;
	}

	const FVector2D ViewportCenter{ViewportSizeX * 0.5f, ViewportSizeY * 0.5f};
	const FVector2D HalfDeadZone{
		FMath::Clamp(DeadZoneWidthRatio, 0.05f, 1.0f) * ViewportSizeX * 0.5f,
		FMath::Clamp(DeadZoneHeightRatio, 0.05f, 1.0f) * ViewportSizeY * 0.5f
	};

	const FVector2D DeadZoneMin = ViewportCenter - HalfDeadZone;
	const FVector2D DeadZoneMax = ViewportCenter + HalfDeadZone;
	const FVector2D ClampedScreenPosition{
		FMath::Clamp(ActorScreenPosition.X, DeadZoneMin.X, DeadZoneMax.X),
		FMath::Clamp(ActorScreenPosition.Y, DeadZoneMin.Y, DeadZoneMax.Y)
	};

	const bool bOutsideDeadZone = !ActorScreenPosition.Equals(ClampedScreenPosition, 0.5f);
	bIsOutsideCameraDeadZone = bOutsideDeadZone;

	if (bOutsideDeadZone)
	{
		FVector DesiredWorldPoint = FVector::ZeroVector;
		if (!DeprojectScreenPositionToGround(ClampedScreenPosition, FPlane{GetActorLocation(), FVector::UpVector}, DesiredWorldPoint))
		{
			return false;
		}

		const FVector AnchorDelta = GetActorLocation() - DesiredWorldPoint;
		OutDesiredAnchor = CameraAnchorLocation + FVector{AnchorDelta.X, AnchorDelta.Y, 0.0f};
		CameraRecenteringTimer = 0.0f;
		bIsCameraRecentering = false;
		return true;
	}

	const FVector HorizontalVelocity{GetVelocity().X, GetVelocity().Y, 0.0f};
	const bool bAllowRecentering =
		RecenteringMode != EAlsTopDownCameraRecenteringMode::Disabled &&
		(!bDisableRecenteringWhileMoving || HorizontalVelocity.SizeSquared() <= FMath::Square(RecenteringMovementThreshold));

	if (!bAllowRecentering)
	{
		CameraRecenteringTimer = 0.0f;
		bIsCameraRecentering = false;
		OutDesiredAnchor = CameraAnchorLocation;
		return true;
	}

	CameraRecenteringTimer += DeltaTime;
	if (CameraRecenteringTimer >= RecenteringDelay)
	{
		bOutShouldRecenter = true;
		bIsCameraRecentering = true;
		OutDesiredAnchor = GetActorLocation();
		return true;
	}

	bIsCameraRecentering = false;
	OutDesiredAnchor = CameraAnchorLocation;
	return true;
}

bool AAlsTopDownCharacter::DeprojectScreenPositionToGround(
	const FVector2D& ScreenPosition,
	const FPlane& GroundPlane,
	FVector& OutWorldPoint) const
{
	const APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (!IsValid(PlayerController))
	{
		return false;
	}

	FVector WorldOrigin = FVector::ZeroVector;
	FVector WorldDirection = FVector::ZeroVector;
	if (!PlayerController->DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, WorldOrigin, WorldDirection))
	{
		return false;
	}

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
