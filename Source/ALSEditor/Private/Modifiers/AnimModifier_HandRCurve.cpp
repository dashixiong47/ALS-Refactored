// Fill out your copyright notice in the Description page of Project Settings.


#include "Modifiers/AnimModifier_HandRCurve.h"


void UAnimModifier_HandRCurve::OnApply_Implementation(UAnimSequence* AnimSequence)
{
	if (!AnimSequence)
	{
		UE_LOG(LogTemp, Warning, TEXT("AnimSequence is null!"));
		return;
	}
	FName HandRBoneName(TEXT("hand_r"));
	// 获取参考帧变换
	FTransform ReferenceWorld;
	if (bUseReferenceAnim)
	{
		ReferenceWorld= GetBoneWorldTransform(AnimSequence, HandRBoneName, SampleFrameNum);
	}
	 
	for (const auto& CurveName : CurveNames)
	{
		// 检查曲线是否已经存在
		if (UAnimationBlueprintLibrary::DoesCurveExist(AnimSequence, CurveName, ERawCurveTrackTypes::RCT_Float))
		{
			UAnimationBlueprintLibrary::RemoveCurve(AnimSequence, CurveName);
		}
		// 添加新的空曲线
		UAnimationBlueprintLibrary::AddCurve(AnimSequence, CurveName);
		for (int32 i = 0; i < AnimSequence->GetNumberOfSampledKeys(); i++)
		{
			FTransform BoneTransform;
			if (bUseReferenceAnim)
			{
				FTransform CurrentWorld = GetBoneWorldTransform(AnimSequence, HandRBoneName, i);
				BoneTransform= ReferenceWorld.Inverse() * CurrentWorld;
			}else
			{
				UAnimationBlueprintLibrary::GetBonePoseForFrame(AnimSequence, CurveName, i, false, BoneTransform);
			}
			
			float Time = AnimSequence->GetTimeAtFrame(i);
			if (CurveName == FName("HandR_PosX"))
			{
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimSequence, CurveName, Time,
				                                             BoneTransform.GetTranslation().X);
			}
			else if (CurveName == FName("HandR_PosY"))
			{
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimSequence, CurveName, Time,
				                                             BoneTransform.GetTranslation().Y);
			}
			else if (CurveName == FName("HandR_PosZ"))
			{
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimSequence, CurveName, Time,
				                                             BoneTransform.GetTranslation().Z);
			}
			else if (CurveName == FName("HandR_RotPitch"))
			{
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimSequence, CurveName, Time,
				                                             BoneTransform.GetRotation().Rotator().Pitch);
			}
			else if (CurveName == FName("HandR_RotYaw"))
			{
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimSequence, CurveName, Time,
				                                             BoneTransform.GetRotation().Rotator().Yaw);
			}
			else if (CurveName == FName("HandR_RotRoll"))
			{
				UAnimationBlueprintLibrary::AddFloatCurveKey(AnimSequence, CurveName, Time,
				                                             BoneTransform.GetRotation().Rotator().Roll);
			}
		}
	}

	

}
FTransform UAnimModifier_HandRCurve::GetBoneWorldTransform(UAnimSequence* AnimSequence, const FName& BoneName, int32 FrameIndex)
{
	FTransform LocalTransform;
	UAnimationBlueprintLibrary::GetBonePoseForFrame(AnimSequence, BoneName, FrameIndex, false, LocalTransform);

	int32 BoneIndex = AnimSequence->GetSkeleton()->GetReferenceSkeleton().FindBoneIndex(BoneName);
	FTransform WorldTransform = LocalTransform;

	// 遍历父级骨骼累积变换
	int32 ParentIndex = AnimSequence->GetSkeleton()->GetReferenceSkeleton().GetParentIndex(BoneIndex);
	while (ParentIndex != INDEX_NONE)
	{
		FName ParentBoneName = AnimSequence->GetSkeleton()->GetReferenceSkeleton().GetBoneName(ParentIndex);
		FTransform ParentTransform;
		UAnimationBlueprintLibrary::GetBonePoseForFrame(AnimSequence, ParentBoneName, FrameIndex, false, ParentTransform);
		WorldTransform = ParentTransform * WorldTransform;
		ParentIndex = AnimSequence->GetSkeleton()->GetReferenceSkeleton().GetParentIndex(ParentIndex);
	}

	return WorldTransform;
}