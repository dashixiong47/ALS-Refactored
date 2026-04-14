#pragma once

#include "AlsCrouchingState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsCrouchingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "步幅混合量", ToolTip = "当前蹲伏移动的步幅混合量。"))
	float StrideBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 2, ForceUnits = "x", DisplayName = "播放速率", ToolTip = "当前蹲伏移动动画的播放速率。"))
	float PlayRate{1.0f};
};
