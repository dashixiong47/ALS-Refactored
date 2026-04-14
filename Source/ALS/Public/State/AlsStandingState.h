#pragma once

#include "AlsStandingState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsStandingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "步幅混合量", ToolTip = "当前站立移动的步幅混合量。"))
	float StrideBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "步行跑步混合量", ToolTip = "步行与跑步之间的混合权重。"))
	float WalkRunBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 3, ForceUnits = "x", DisplayName = "播放速率", ToolTip = "当前站立移动动画的播放速率。"))
	float PlayRate{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "冲刺阻断量", ToolTip = "当前用于抑制冲刺表现的权重。"))
	float SprintBlockAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "冲刺时间", ToolTip = "当前已累计的冲刺持续时间。"))
	float SprintTime{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -1, ClampMax = 1, DisplayName = "冲刺加速度量", ToolTip = "当前冲刺加速度的归一化量。"))
	float SprintAccelerationAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "轴点已激活", ToolTip = "当前是否处于 Pivot 激活状态。"))
	uint8 bPivotActive : 1 {false};
};
