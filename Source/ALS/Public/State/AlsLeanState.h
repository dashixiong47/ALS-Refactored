#pragma once

#include "AlsLeanState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsLeanState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -1, ClampMax = 1, DisplayName = "右向倾斜量", ToolTip = "角色当前的左右倾斜量。"))
	float RightAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -1, ClampMax = 1, DisplayName = "前向倾斜量", ToolTip = "角色当前的前后倾斜量。"))
	float ForwardAmount{0.0f};
};
