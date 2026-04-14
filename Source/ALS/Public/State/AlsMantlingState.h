#pragma once

#include "AlsMantlingState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "根运动源 ID", ToolTip = "当前翻越动作使用的根运动源编号。"))
	int32 RootMotionSourceId{0};
};
