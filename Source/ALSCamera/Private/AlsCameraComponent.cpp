#include "AlsCameraComponent.h"

#include "AlsCameraSettings.h"
#include "AlsCharacter.h"
#include "DrawDebugHelpers.h"
#include "Animation/AnimInstance.h"
#include "Engine/OverlapResult.h"
#include "GameFramework/Character.h"
#include "GameFramework/WorldSettings.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utility/AlsCameraConstants.h"
#include "Utility/AlsDebugUtility.h"
#include "Utility/AlsMacros.h"
#include "Utility/AlsRotation.h"
#include "Utility/AlsUtility.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsCameraComponent)

UAlsCameraComponent::UAlsCameraComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;
	PrimaryComponentTick.TickGroup = TG_PostPhysics;

	bTickInEditor = false;
	bHiddenInGame = true;
}

void UAlsCameraComponent::OnRegister()
{
	Character = Cast<ACharacter>(GetOwner());

	Super::OnRegister();
}

void UAlsCameraComponent::RegisterComponentTickFunctions(const bool bRegister)
{
	Super::RegisterComponentTickFunctions(bRegister);

	// Tick after the owner to have access to the most up-to-date character state.

	AddTickPrerequisiteActor(GetOwner());
}

void UAlsCameraComponent::Activate(const bool bReset)
{
	if (bReset || ShouldActivate())
	{
		TickCamera(0.0f, false);
	}

	Super::Activate(bReset);
}

void UAlsCameraComponent::InitAnim(const bool bForceReinitialize)
{
	Super::InitAnim(bForceReinitialize);

	AnimationInstance = GetAnimInstance();
}

void UAlsCameraComponent::BeginPlay()
{
	ALS_ENSURE(IsValid(GetAnimInstance()));
	ALS_ENSURE(IsValid(Settings));
	ALS_ENSURE(IsValid(Character));

	Super::BeginPlay();
}

void UAlsCameraComponent::TickComponent(float DeltaTime, const ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (IsValid(Settings) && Settings->bIgnoreTimeDilation)
	{
		// Use the previous global time dilation, as this frame's delta time may not yet be affected
		// by the current global time dilation, and thus unscaling will produce the wrong delta time.

		const auto TimeDilation{PreviousGlobalTimeDilation * GetOwner()->CustomTimeDilation};

		DeltaTime = TimeDilation > UE_SMALL_NUMBER ? DeltaTime / TimeDilation : GetWorld()->DeltaRealTimeSeconds;
	}

	PreviousGlobalTimeDilation = GetWorld()->GetWorldSettings()->GetEffectiveTimeDilation();

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Skip camera tick until parallel animation evaluation completes.

	if (!IsRunningParallelEvaluation())
	{
		TickCamera(DeltaTime);
	}
}

void UAlsCameraComponent::CompleteParallelAnimationEvaluation(const bool bDoPostAnimationEvaluation)
{
	Super::CompleteParallelAnimationEvaluation(bDoPostAnimationEvaluation);

	TickCamera(GetAnimInstance()->GetDeltaSeconds());
}

FVector UAlsCameraComponent::GetFirstPersonCameraLocation() const
{
	return Character->GetMesh()->GetSocketLocation(Settings->FirstPerson.CameraSocketName);
}

FVector UAlsCameraComponent::GetThirdPersonPivotLocation() const
{
	const auto* Mesh{Character->GetMesh()};

	FVector FirstPivotLocation;

	if (!IsValid(Mesh->GetAttachParent()) && Settings->ThirdPerson.FirstPivotSocketName == UAlsConstants::RootBoneName())
	{
		// The root bone location usually remains fixed when the mesh is detached, so use the capsule's bottom location here as a fallback.

		FirstPivotLocation = Character->GetRootComponent()->GetComponentLocation();
		FirstPivotLocation.Z -= Character->GetRootComponent()->Bounds.BoxExtent.Z;
	}
	else
	{
		FirstPivotLocation = Mesh->GetSocketLocation(Settings->ThirdPerson.FirstPivotSocketName);
	}

	return (FirstPivotLocation + Mesh->GetSocketLocation(Settings->ThirdPerson.SecondPivotSocketName)) * 0.5f;
}

FVector UAlsCameraComponent::GetThirdPersonTraceStartLocation() const
{
	return Character->GetMesh()->GetSocketLocation(bRightShoulder
		                                               ? Settings->ThirdPerson.TraceShoulderRightSocketName
		                                               : Settings->ThirdPerson.TraceShoulderLeftSocketName);
}

void UAlsCameraComponent::GetViewInfo(FMinimalViewInfo& ViewInfo) const
{
	ViewInfo.Location = CameraLocation;
	ViewInfo.Rotation = CameraRotation;
	ViewInfo.FOV = CameraFieldOfView;

	ViewInfo.PostProcessBlendWeight = IsValid(Settings) ? PostProcessWeight : 0.0f;

	if (ViewInfo.PostProcessBlendWeight > UE_SMALL_NUMBER)
	{
		ViewInfo.PostProcessSettings = Settings->PostProcess;
	}
}

void UAlsCameraComponent::TickCamera(const float DeltaTime, bool bAllowLag)
{
	// 性能统计相关宏（用于性能分析）
	DECLARE_SCOPE_CYCLE_COUNTER(TEXT("UAlsCameraComponent::TickCamera"), STAT_UAlsCameraComponent_TickCamera, STATGROUP_Als)
	TRACE_CPUPROFILER_EVENT_SCOPE(UAlsCameraComponent::TickCamera);

	// 如果动画实例、配置、角色无效，直接返回
	if (!IsValid(GetAnimInstance()) || !IsValid(Settings) || !IsValid(Character))
	{
		return;
	}

	// 检查是否在并行动画评估中调用（防止访问曲线卡主线程）
	ALS_ENSURE_MESSAGE(!IsRunningParallelEvaluation(),
	                   TEXT("%hs should not be called during parallel animation evaluation, because accessing animation curves")
	                   TEXT(" causes the game thread to wait for the parallel task to complete, resulting in performance degradation."),
	                   __FUNCTION__);

#if ENABLE_DRAW_DEBUG
	// 是否显示调试摄像机形状
	const auto bDisplayDebugCameraShapes{
		UAlsDebugUtility::ShouldDisplayDebugForActor(GetOwner(), UAlsCameraConstants::CameraShapesDebugDisplayName())
	};
#else
	const auto bDisplayDebugCameraShapes{false};
#endif

	// 刷新 Movement Base（角色当前所站立的平台）

	const auto& BasedMovement{Character->GetBasedMovement()};
	const auto bMovementBaseHasRelativeRotation{BasedMovement.HasRelativeRotation()};

	auto MovementBaseLocation{FVector::ZeroVector};
	auto MovementBaseRotation{FQuat::Identity};

	// 如果基底有旋转，获取基底的世界空间位置和旋转
	if (bMovementBaseHasRelativeRotation)
	{
		MovementBaseUtility::GetMovementBaseTransform(BasedMovement.MovementBase, BasedMovement.BoneName,
		                                              MovementBaseLocation, MovementBaseRotation);
	}

	// 如果 MovementBase 发生变化，则更新相对位置/旋转
	if (BasedMovement.MovementBase != MovementBasePrimitive || BasedMovement.BoneName != MovementBaseBoneName)
	{
		MovementBasePrimitive = BasedMovement.MovementBase;
		MovementBaseBoneName = BasedMovement.BoneName;

		if (bMovementBaseHasRelativeRotation)
		{
			const auto MovementBaseRotationInverse{MovementBaseRotation.Inverse()};

			// 记录相对基底的滞后位置
			PivotMovementBaseRelativeLagLocation = MovementBaseRotationInverse.RotateVector(PivotLagLocation - MovementBaseLocation);
			// 记录相对基底的摄像机旋转
			CameraMovementBaseRelativeRotation = MovementBaseRotationInverse * CameraRotation.Quaternion();
		}
		else
		{
			PivotMovementBaseRelativeLagLocation = FVector::ZeroVector;
			CameraMovementBaseRelativeRotation = FQuat::Identity;
		}
	}

	// 角色当前目标视角（控制器旋转）
	const auto CameraTargetRotation{Character->GetViewRotation()};

	// 保存上帧的 Pivot 位置
	const auto PreviousPivotTargetLocation{PivotTargetLocation};

	// 计算新的 Pivot 目标位置
	PivotTargetLocation = GetThirdPersonPivotLocation();

	// 动画曲线：是否启用第一人称（0~1）
	const auto FirstPersonOverride{
		UAlsMath::Clamp01(GetAnimInstance()->GetCurveValue(UAlsCameraConstants::FirstPersonOverrideCurveName()))
	};

	if (FAnimWeight::IsFullWeight(FirstPersonOverride))
	{
		// 如果完全是第一人称模式，跳过后续所有第三人称的计算
		PivotLagLocation = PivotTargetLocation;
		PivotLocation = PivotTargetLocation;

		CameraLocation = GetFirstPersonCameraLocation();
		CameraRotation = CameraTargetRotation;

		CameraFieldOfView = bOverrideFieldOfView ? FieldOfViewOverride : Settings->FirstPerson.FieldOfView;
		return;
	}

	// 如果角色瞬移（位移过大），强制禁用镜头延迟（Lag）
	bAllowLag &= Settings->TeleportDistanceThreshold <= 0.0f ||
		FVector::DistSquared(PreviousPivotTargetLocation, PivotTargetLocation) <= FMath::Square(Settings->TeleportDistanceThreshold);

	// 计算摄像机旋转
	if (bMovementBaseHasRelativeRotation)
	{
		// 如果站在可旋转的平台上，需要基于平台旋转计算
		CameraRotation = (MovementBaseRotation * CameraMovementBaseRelativeRotation).Rotator();
		CameraRotation = CalculateCameraRotation(CameraTargetRotation, DeltaTime, bAllowLag);
		CameraMovementBaseRelativeRotation = MovementBaseRotation.Inverse() * CameraRotation.Quaternion();
	}
	else
	{
		CameraRotation = CalculateCameraRotation(CameraTargetRotation, DeltaTime, bAllowLag);
	}

	const FQuat CameraYawRotation{FVector::ZAxisVector, FMath::DegreesToRadians(CameraRotation.Yaw)};

#if ENABLE_DRAW_DEBUG
	// Debug 绘制：Pivot 目标位置
	if (bDisplayDebugCameraShapes)
	{
		UAlsDebugUtility::DrawSphereAlternative(GetWorld(), PivotTargetLocation, CameraYawRotation.Rotator(), 16.0f, FLinearColor::Green);
	}
#endif

	// 计算 Pivot 滞后位置
	if (bMovementBaseHasRelativeRotation)
	{
		PivotLagLocation = MovementBaseLocation + MovementBaseRotation.RotateVector(PivotMovementBaseRelativeLagLocation);
		PivotLagLocation = CalculatePivotLagLocation(CameraYawRotation, DeltaTime, bAllowLag);
		PivotMovementBaseRelativeLagLocation = MovementBaseRotation.UnrotateVector(PivotLagLocation - MovementBaseLocation);
	}
	else
	{
		PivotLagLocation = CalculatePivotLagLocation(CameraYawRotation, DeltaTime, bAllowLag);
	}

#if ENABLE_DRAW_DEBUG
	// Debug 绘制：Pivot 滞后位置
	if (bDisplayDebugCameraShapes)
	{
		DrawDebugLine(GetWorld(), PivotLagLocation, PivotTargetLocation,
		              FLinearColor{1.0f, 0.5f, 0.0f}.ToFColor(true),
		              false, 0.0f, 0, UAlsDebugUtility::DrawLineThickness);

		UAlsDebugUtility::DrawSphereAlternative(GetWorld(), PivotLagLocation, CameraYawRotation.Rotator(), 16.0f, {1.0f, 0.5f, 0.0f});
	}
#endif

	// 计算最终 Pivot 位置（滞后位置 + 偏移）
	const auto PivotOffset{CalculatePivotOffset()};
	PivotLocation = PivotLagLocation + PivotOffset;

#if ENABLE_DRAW_DEBUG
	// Debug 绘制：Pivot 最终位置
	if (bDisplayDebugCameraShapes)
	{
		DrawDebugLine(GetWorld(), PivotLocation, PivotLagLocation,
		              FLinearColor{0.0f, 0.75f, 1.0f}.ToFColor(true),
		              false, 0.0f, 0, UAlsDebugUtility::DrawLineThickness);

		UAlsDebugUtility::DrawSphereAlternative(GetWorld(), PivotLocation, CameraYawRotation.Rotator(), 16.0f, {0.0f, 0.75f, 1.0f});
	}
#endif

	// 计算目标摄像机位置（Pivot + 摄像机偏移）
	const auto CameraTargetLocation{PivotLocation + CalculateCameraOffset()};

	// 碰撞检测修正摄像机位置（避免穿模）
	const auto CameraFinalLocation{CalculateCameraTrace(CameraTargetLocation, PivotOffset, DeltaTime, bAllowLag, TraceDistanceRatio)};

	// 计算最终摄像机位置 & FOV（考虑第一人称混合）
	if (!FAnimWeight::IsRelevant(FirstPersonOverride))
	{
		CameraLocation = CameraFinalLocation;
		CameraFieldOfView = Settings->ThirdPerson.FieldOfView;
	}
	else
	{
		CameraLocation = FMath::Lerp(CameraFinalLocation, GetFirstPersonCameraLocation(), FirstPersonOverride);
		CameraFieldOfView = FMath::Lerp(Settings->ThirdPerson.FieldOfView, Settings->FirstPerson.FieldOfView, FirstPersonOverride);
	}

	// 如果手动指定 FOV，覆盖
	if (bOverrideFieldOfView)
	{
		CameraFieldOfView = FieldOfViewOverride;
	}

	// 限制 FOV 范围并应用动态偏移
	CameraFieldOfView = FMath::Clamp(CameraFieldOfView + CalculateFovOffset(), 5.0f, 175.0f);
}


FRotator UAlsCameraComponent::CalculateCameraRotation(const FRotator& CameraTargetRotation,
                                                      const float DeltaTime, const bool bAllowLag) const
{
	// 如果不允许相机滞后（Lag），直接返回目标旋转
	if (!bAllowLag)
	{
		return CameraTargetRotation;
	}

	// 从动画曲线中获取相机旋转滞后系数（可动态控制）
	const auto RotationLag{GetAnimInstance()->GetCurveValue(UAlsCameraConstants::RotationLagCurveName())};

	// 如果禁用子步滞后 或 DeltaTime 太小 或 曲线系数为 0
	// 就直接用指数衰减方式计算相机旋转
	if (!Settings->bEnableCameraLagSubstepping ||
	    DeltaTime <= Settings->CameraLagSubstepping.LagSubstepDeltaTime ||
	    RotationLag <= 0.0f)
	{
		return UAlsRotation::ExponentialDecayRotation(CameraRotation, CameraTargetRotation, DeltaTime, RotationLag);
	}

	// 记录当前相机旋转
	const auto CameraInitialRotation{CameraRotation};

	// 计算每秒旋转速度（目标 - 当前）/ DeltaTime
	const auto SubstepRotationSpeed{(CameraTargetRotation - CameraInitialRotation).GetNormalized() * (1.0f / DeltaTime)};

	// 用来累积每个子步计算结果
	auto NewCameraRotation{CameraRotation};
	auto PreviousSubstepTime{0.0f};

	// 子步循环，逐步逼近目标旋转
	for (auto SubstepNumber{1};; SubstepNumber++)
	{
		// 当前子步时间（子步编号 × 每子步时间长度）
		const auto SubstepTime{SubstepNumber * Settings->CameraLagSubstepping.LagSubstepDeltaTime};

		// 如果子步时间小于本帧总时间（DeltaTime）
		if (SubstepTime < DeltaTime - UE_SMALL_NUMBER)
		{
			// 逐帧插值到当前子步应当到达的位置
			NewCameraRotation = FMath::RInterpTo(
				NewCameraRotation,                                                  // 当前旋转
				CameraInitialRotation + SubstepRotationSpeed * SubstepTime,         // 目标：初始旋转 + 旋转速度 * 时间
				SubstepTime - PreviousSubstepTime,                                  // 当前子步时间增量
				RotationLag                                                         // 滞后系数
			);

			// 更新上一次子步的时间
			PreviousSubstepTime = SubstepTime;
		}
		else
		{
			// 最后一次插值，插到真正的目标旋转
			return FMath::RInterpTo(
				NewCameraRotation,               // 当前旋转
				CameraTargetRotation,            // 最终目标旋转
				DeltaTime - PreviousSubstepTime, // 最后剩余的子步时间
				RotationLag                      // 滞后系数
			);
		}
	}
}


FVector UAlsCameraComponent::CalculatePivotLagLocation(const FQuat& CameraYawRotation, const float DeltaTime, const bool bAllowLag) const
{
	if (!bAllowLag)
	{
		return PivotTargetLocation;
	}

	const auto RelativePivotInitialLagLocation{CameraYawRotation.UnrotateVector(PivotLagLocation)};
	const auto RelativePivotTargetLocation{CameraYawRotation.UnrotateVector(PivotTargetLocation)};

	const auto LocationLagX{GetAnimInstance()->GetCurveValue(UAlsCameraConstants::LocationLagXCurveName())};
	const auto LocationLagY{GetAnimInstance()->GetCurveValue(UAlsCameraConstants::LocationLagYCurveName())};
	const auto LocationLagZ{GetAnimInstance()->GetCurveValue(UAlsCameraConstants::LocationLagZCurveName())};

	if (!Settings->bEnableCameraLagSubstepping ||
	    DeltaTime <= Settings->CameraLagSubstepping.LagSubstepDeltaTime ||
	    (LocationLagX <= 0.0f && LocationLagY <= 0.0f && LocationLagZ <= 0.0f))
	{
		return CameraYawRotation.RotateVector({
			UAlsMath::ExponentialDecay(RelativePivotInitialLagLocation.X, RelativePivotTargetLocation.X, DeltaTime, LocationLagX),
			UAlsMath::ExponentialDecay(RelativePivotInitialLagLocation.Y, RelativePivotTargetLocation.Y, DeltaTime, LocationLagY),
			UAlsMath::ExponentialDecay(RelativePivotInitialLagLocation.Z, RelativePivotTargetLocation.Z, DeltaTime, LocationLagZ)
		});
	}

	const auto SubstepMovementSpeed{(RelativePivotTargetLocation - RelativePivotInitialLagLocation) / DeltaTime};

	auto RelativePivotLagLocation{RelativePivotInitialLagLocation};
	auto PreviousSubstepTime{0.0f};

	for (auto SubstepNumber{1};; SubstepNumber++)
	{
		const auto SubstepTime{SubstepNumber * Settings->CameraLagSubstepping.LagSubstepDeltaTime};
		if (SubstepTime < DeltaTime - UE_SMALL_NUMBER)
		{
			const auto SubstepRelativePivotTargetLocation{RelativePivotInitialLagLocation + SubstepMovementSpeed * SubstepTime};
			const auto SubstepDeltaTime{SubstepTime - PreviousSubstepTime};

			RelativePivotLagLocation.X = FMath::FInterpTo(RelativePivotLagLocation.X, SubstepRelativePivotTargetLocation.X,
			                                              SubstepDeltaTime, LocationLagX);
			RelativePivotLagLocation.Y = FMath::FInterpTo(RelativePivotLagLocation.Y, SubstepRelativePivotTargetLocation.Y,
			                                              SubstepDeltaTime, LocationLagY);
			RelativePivotLagLocation.Z = FMath::FInterpTo(RelativePivotLagLocation.Z, SubstepRelativePivotTargetLocation.Z,
			                                              SubstepDeltaTime, LocationLagZ);

			PreviousSubstepTime = SubstepTime;
		}
		else
		{
			const auto RemainingDeltaTime{DeltaTime - PreviousSubstepTime};

			RelativePivotLagLocation.X = FMath::FInterpTo(RelativePivotLagLocation.X, RelativePivotTargetLocation.X,
			                                              RemainingDeltaTime, LocationLagX);
			RelativePivotLagLocation.Y = FMath::FInterpTo(RelativePivotLagLocation.Y, RelativePivotTargetLocation.Y,
			                                              RemainingDeltaTime, LocationLagY);
			RelativePivotLagLocation.Z = FMath::FInterpTo(RelativePivotLagLocation.Z, RelativePivotTargetLocation.Z,
			                                              RemainingDeltaTime, LocationLagZ);

			return CameraYawRotation.RotateVector(RelativePivotLagLocation);
		}
	}
}

FVector UAlsCameraComponent::CalculatePivotOffset() const
{
	return Character->GetMesh()->GetComponentQuat().RotateVector(
		FVector{
			GetAnimInstance()->GetCurveValue(UAlsCameraConstants::PivotOffsetXCurveName()),
			GetAnimInstance()->GetCurveValue(UAlsCameraConstants::PivotOffsetYCurveName()),
			GetAnimInstance()->GetCurveValue(UAlsCameraConstants::PivotOffsetZCurveName())
		} * Character->GetMesh()->GetComponentScale().Z);
}

FVector UAlsCameraComponent::CalculateCameraOffset() const
{
	return CameraRotation.RotateVector(
		FVector{
			GetAnimInstance()->GetCurveValue(UAlsCameraConstants::CameraOffsetXCurveName()),
			GetAnimInstance()->GetCurveValue(UAlsCameraConstants::CameraOffsetYCurveName()),
			GetAnimInstance()->GetCurveValue(UAlsCameraConstants::CameraOffsetZCurveName())
		} * Character->GetMesh()->GetComponentScale().Z);
}

float UAlsCameraComponent::CalculateFovOffset() const
{
	return GetAnimInstance()->GetCurveValue(UAlsCameraConstants::FovOffsetCurveName());
}

FVector UAlsCameraComponent::CalculateCameraTrace(const FVector& CameraTargetLocation, const FVector& PivotOffset,
                                                  const float DeltaTime, const bool bAllowLag, float& NewTraceDistanceRatio) const
{
#if ENABLE_DRAW_DEBUG
	const auto bDisplayDebugCameraTraces{
		UAlsDebugUtility::ShouldDisplayDebugForActor(GetOwner(), UAlsCameraConstants::CameraTracesDebugDisplayName())
	};
#else
	const auto bDisplayDebugCameraTraces{false};
#endif

	const auto MeshScale{UE_REAL_TO_FLOAT(Character->GetMesh()->GetComponentScale().Z)};

	static const FName MainTraceTag{FString::Printf(TEXT("%hs (Main Trace)"), __FUNCTION__)};

	auto TraceStart{
		FMath::Lerp(
			GetThirdPersonTraceStartLocation(),
			PivotTargetLocation + PivotOffset + FVector{Settings->ThirdPerson.TraceOverrideOffset},
			UAlsMath::Clamp01(GetAnimInstance()->GetCurveValue(UAlsCameraConstants::TraceOverrideCurveName())))
	};

	const auto TraceEnd{CameraTargetLocation};
	const auto CollisionShape{FCollisionShape::MakeSphere(Settings->ThirdPerson.TraceRadius * MeshScale)};

	auto TraceResult{TraceEnd};

	FHitResult Hit;
	if (GetWorld()->SweepSingleByChannel(Hit, TraceStart, TraceEnd, FQuat::Identity, Settings->ThirdPerson.TraceChannel,
	                                     CollisionShape, {MainTraceTag, false, GetOwner()}))
	{
		if (!Hit.bStartPenetrating)
		{
			TraceResult = Hit.Location;
		}
		else if (TryAdjustLocationBlockedByGeometry(TraceStart, bDisplayDebugCameraTraces))
		{
			static const FName AdjustedTraceTag{FString::Printf(TEXT("%hs (Adjusted Trace)"), __FUNCTION__)};

			GetWorld()->SweepSingleByChannel(Hit, TraceStart, TraceEnd, FQuat::Identity, Settings->ThirdPerson.TraceChannel,
			                                 CollisionShape, {AdjustedTraceTag, false, GetOwner()});
			if (Hit.IsValidBlockingHit())
			{
				TraceResult = Hit.Location;
			}
		}
		else
		{
			// Note that TraceStart may be changed even if TryAdjustLocationBlockedByGeometry() returned false.
			TraceResult = TraceStart;
		}
	}

#if ENABLE_DRAW_DEBUG
	if (bDisplayDebugCameraTraces)
	{
		UAlsDebugUtility::DrawSweepSphere(GetWorld(), TraceStart, TraceResult, CollisionShape.GetCapsuleRadius(),
		                                  Hit.IsValidBlockingHit() ? FLinearColor::Red : FLinearColor::Green);
	}
#endif

	// Apply trace distance smoothing.

	if (!bAllowLag || !Settings->ThirdPerson.bEnableTraceDistanceSmoothing)
	{
		NewTraceDistanceRatio = 1.0f;
		return TraceResult;
	}

	const auto TraceVector{TraceEnd - TraceStart};
	const auto TraceDistance{TraceVector.Size()};

	if (TraceDistance <= UE_KINDA_SMALL_NUMBER)
	{
		NewTraceDistanceRatio = 1.0f;
		return TraceResult;
	}

	const auto TargetTraceDistanceRatio{UE_REAL_TO_FLOAT((TraceResult - TraceStart).Size() / TraceDistance)};

	NewTraceDistanceRatio = TargetTraceDistanceRatio <= TraceDistanceRatio
		                        ? TargetTraceDistanceRatio
		                        : UAlsMath::ExponentialDecay(TraceDistanceRatio, TargetTraceDistanceRatio, DeltaTime,
		                                                     Settings->ThirdPerson.TraceDistanceSmoothing.InterpolationSpeed);

	return TraceStart + TraceVector * TraceDistanceRatio;
}

bool UAlsCameraComponent::TryAdjustLocationBlockedByGeometry(FVector& Location, const bool bDisplayDebugCameraTraces) const
{
	// Based on ComponentEncroachesBlockingGeometry_WithAdjustment().

	const auto MeshScale{UE_REAL_TO_FLOAT(Character->GetMesh()->GetComponentScale().Z)};
	const auto CollisionShape{FCollisionShape::MakeSphere((Settings->ThirdPerson.TraceRadius + 1.0f) * MeshScale)};

	static TArray<FOverlapResult> Overlaps;
	check(Overlaps.IsEmpty())

	ON_SCOPE_EXIT
	{
		Overlaps.Reset();
	};

	static const FName OverlapMultiTraceTag{FString::Printf(TEXT("%hs (Overlap Multi)"), __FUNCTION__)};

	if (!GetWorld()->OverlapMultiByChannel(Overlaps, Location, FQuat::Identity, Settings->ThirdPerson.TraceChannel,
	                                       CollisionShape, {OverlapMultiTraceTag, false, GetOwner()}))
	{
		return false;
	}

	auto Adjustment{FVector::ZeroVector};
	auto bAnyValidBlock{false};

	FMTDResult MtdResult;

	for (const auto& Overlap : Overlaps)
	{
		if (!Overlap.Component.IsValid() ||
		    Overlap.Component->GetCollisionResponseToChannel(Settings->ThirdPerson.TraceChannel) != ECR_Block)
		{
			continue;
		}

		const auto* OverlapBody{Overlap.Component->GetBodyInstance(NAME_None, true, Overlap.ItemIndex)};

		if (OverlapBody == nullptr || !OverlapBody->OverlapTest(Location, FQuat::Identity, CollisionShape, &MtdResult))
		{
			return false;
		}

		if (!FMath::IsNearlyZero(MtdResult.Distance))
		{
			Adjustment += MtdResult.Direction * MtdResult.Distance;
			bAnyValidBlock = true;
		}
	}

	if (!bAnyValidBlock)
	{
		return false;
	}

	auto AdjustmentDirection{Adjustment};

	if (!AdjustmentDirection.Normalize() ||
	    ((GetOwner()->GetActorLocation() - Location).GetSafeNormal() | AdjustmentDirection) < -UE_KINDA_SMALL_NUMBER)
	{
		return false;
	}

#if ENABLE_DRAW_DEBUG
	if (bDisplayDebugCameraTraces)
	{
		DrawDebugLine(GetWorld(), Location, Location + Adjustment,
		              FLinearColor{0.0f, 0.75f, 1.0f}.ToFColor(true),
		              false, 5.0f, 0, UAlsDebugUtility::DrawLineThickness);
	}
#endif

	Location += Adjustment;

	static const FName FreeSpaceTraceTag{FString::Printf(TEXT("%hs (Free Space Overlap)"), __FUNCTION__)};

	return !GetWorld()->OverlapBlockingTestByChannel(Location, FQuat::Identity, Settings->ThirdPerson.TraceChannel,
	                                                 FCollisionShape::MakeSphere(Settings->ThirdPerson.TraceRadius * MeshScale),
	                                                 {FreeSpaceTraceTag, false, GetOwner()});
}
