#include "Nodes/AlsRigUnit_DistributeSpineAdvanced.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsRigUnit_DistributeSpineAdvanced)
FAlsRigUnit_DistributeSpineAdvanced_Execute()
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_RIGUNIT()

	auto* Hierarchy = ExecuteContext.Hierarchy;
	if (!IsValid(Hierarchy))
	{
		return;
	}

	const bool bDoYaw = SpineRotationState == ESpineRotationState::YawOnly || SpineRotationState ==
		ESpineRotationState::YawAndPitch;
	const bool bDoPitch = SpineRotationState == ESpineRotationState::PitchOnly || SpineRotationState ==
		ESpineRotationState::YawAndPitch;

	// --- Pitch 处理 ---
	if (bDoPitch && !FMath::IsNearlyZero(PitchAngle, KINDA_SMALL_NUMBER))
	{
		const bool bLookUp = PitchAngle > 0.0f;

		TArrayView<const FRigElementKey> TargetBones = bLookUp ? SpinePitchUpBones : SpinePitchDownBones;
		TArrayView<const float> TargetWeights = bLookUp ? SpinePitchUpWeights : SpinePitchDownWeights;
		TArray<FCachedRigElement>& CachedBones = bLookUp ? CachedSpinePitchUpBones : CachedSpinePitchDownBones;

		if (TargetBones.Num() > 0 && TargetBones.Num() == TargetWeights.Num())
		{
			float TotalWeight = 0.0f;
			for (float W : TargetWeights)
			{
				TotalWeight += W;
			}
			if (TotalWeight <= KINDA_SMALL_NUMBER)
			{
				TotalWeight = 1.0f;
			}

			if (CachedBones.Num() != TargetBones.Num())
			{
				CachedBones.SetNum(TargetBones.Num());
			}

			for (int32 i = 0; i < TargetBones.Num(); i++)
			{
				const FRigElementKey& BoneKey = TargetBones[i];
				const float NormalizedWeight = TargetWeights[i] / TotalWeight;

				if (CachedBones[i].UpdateCache(BoneKey, Hierarchy))
				{
					FTransform NewTransform = Hierarchy->GetGlobalTransform(CachedBones[i]);
					const float AppliedPitch = PitchAngle * NormalizedWeight;
					const FQuat PitchQuat(FVector::ForwardVector, FMath::DegreesToRadians(AppliedPitch));
					NewTransform.SetRotation(PitchQuat * NewTransform.GetRotation());
					Hierarchy->SetGlobalTransform(CachedBones[i], NewTransform);
				}
			}
		}
	}


	// --- Yaw 处理 ---
	if (bDoYaw && SpineYawBone.IsValid() && !FMath::IsNearlyZero(YawAngle, KINDA_SMALL_NUMBER))
	{
		if (CachedSpineYawBone.UpdateCache(SpineYawBone, Hierarchy))
		{
			FTransform NewTransform = Hierarchy->GetGlobalTransform(CachedSpineYawBone);
			const FQuat YawQuat(FVector::UpVector, FMath::DegreesToRadians(YawAngle));
			NewTransform.SetRotation(YawQuat * NewTransform.GetRotation());
			Hierarchy->SetGlobalTransform(CachedSpineYawBone, NewTransform);
		}
	}
}
