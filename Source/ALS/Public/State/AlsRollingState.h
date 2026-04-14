#pragma once

#include "AlsRollingState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsRollingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "目标偏航角", ToolTip = "当前翻滚动作使用的目标偏航角。"))
	float TargetYawAngle{0.0f};
};
