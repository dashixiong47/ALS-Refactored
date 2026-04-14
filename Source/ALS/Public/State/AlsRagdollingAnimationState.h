#pragma once

#include "Animation/PoseSnapshot.h"
#include "AlsRagdollingAnimationState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsRagdollingAnimationState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "最终布娃娃姿势", ToolTip = "布娃娃结束时缓存的最终姿势快照。"))
	FPoseSnapshot FinalRagdollPose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, ForceUnits = "x", DisplayName = "摆动播放速率", ToolTip = "布娃娃摆动动画的播放速率。"))
	float FlailPlayRate{1.0f};
};
