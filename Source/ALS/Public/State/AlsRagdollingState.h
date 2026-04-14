#pragma once

#include "AlsRagdollingState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsRagdollingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "速度", ToolTip = "当前布娃娃状态的速度向量。"))
	FVector Velocity{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ForceUnits = "N", DisplayName = "拉力", ToolTip = "布娃娃恢复或拉拽时施加的力。"))
	float PullForce{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, DisplayName = "速度限制剩余帧数", ToolTip = "布娃娃初始速度限制还会持续多少帧。"))
	int32 SpeedLimitFrameTimeRemaining{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "速度限制", ToolTip = "布娃娃初始阶段允许的最大速度。"))
	float SpeedLimit{0.0f};
};
