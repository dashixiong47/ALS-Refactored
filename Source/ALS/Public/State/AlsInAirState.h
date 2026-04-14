#pragma once

#include "AlsInAirState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsInAirState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ForceUnits = "cm/s", DisplayName = "垂直速度", ToolTip = "角色当前的垂直速度。"))
	float VerticalVelocity{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "已请求跳跃", ToolTip = "当前是否已经请求跳跃。"))
	uint8 bJumpRequested : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "已起跳", ToolTip = "当前是否已经进入起跳状态。"))
	uint8 bJumped : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "跳跃播放速率", ToolTip = "跳跃动画的播放速率。"))
	float JumpPlayRate{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "地面预测量", ToolTip = "当前空中状态下的地面预测权重。"))
	float GroundPredictionAmount{1.0f};
};
