#pragma once

#include "AlsDynamicTransitionsSettings.generated.h"

class UAnimSequenceBase;

USTRUCT(BlueprintType)
struct ALS_API FAlsDynamicTransitionsSettings
{
	GENERATED_BODY()

	// 脚锁距离阈值（厘米）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm"), DisplayName="脚锁距离阈值")
	float FootLockDistanceThreshold{8.0f};

	// 混合持续时间（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName="混合持续时间")
	float BlendDuration{0.2f};

	// 播放速率
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "x"), DisplayName="播放速率")
	float PlayRate{1.5f};

	// 站立向左动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="站立向左动画序列")
	TObjectPtr<UAnimSequenceBase> StandingLeftSequence;

	// 站立向右动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="站立向右动画序列")
	TObjectPtr<UAnimSequenceBase> StandingRightSequence;

	// 蹲下向左动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="蹲下向左动画序列")
	TObjectPtr<UAnimSequenceBase> CrouchingLeftSequence;

	// 蹲下向右动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="蹲下向右动画序列")
	TObjectPtr<UAnimSequenceBase> CrouchingRightSequence;

};
