// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimationModifier.h"
#include "AnimModifier_HandRCurve.generated.h"

/**
 * 自动采样动画中 hand_r 骨骼的 位置/旋转 信息，并生成对应曲线：
 * HandR_PosX / HandR_PosY / HandR_PosZ
 * HandR_RotPitch / HandR_RotYaw / HandR_RotRoll
 */
UCLASS()
class UAnimModifier_HandRCurve : public UAnimationModifier
{
	GENERATED_BODY()

public:
	TArray<FName> CurveNames
	{
		TEXT("HandR_PosX"),
		TEXT("HandR_PosY"),
		TEXT("HandR_PosZ"),
		TEXT("HandR_RotPitch"),
		TEXT("HandR_RotYaw"),
		TEXT("HandR_RotRoll"),
	};
	UPROPERTY(EditAnywhere , BlueprintReadOnly, Category = "Settings", DisplayName="是否使用参考动画")
	bool bUseReferenceAnim{true};
	// 参考动画帧
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="参考动画帧")
	UAnimSequence* ReferenceAnimSequence{nullptr};
	// 帧数
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 1), DisplayName="采样帧数")
	int32 SampleFrameNum{0};
	
public:
	/** 当 Modifier 被应用到动画时调用（主逻辑入口） */
	virtual void OnApply_Implementation(UAnimSequence* AnimSequence) override;
	FTransform GetBoneWorldTransform(UAnimSequence* AnimSequence, const FName& BoneName, int32 FrameIndex);
};
