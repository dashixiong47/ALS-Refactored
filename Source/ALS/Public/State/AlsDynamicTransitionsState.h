#pragma once

#include "AlsDynamicTransitionsState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsDynamicTransitionsState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "本帧已更新", ToolTip = "当前动态过渡状态是否已在本帧更新。"))
	uint8 bUpdatedThisFrame : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "帧延迟", ToolTip = "动态过渡激活前剩余的帧延迟。"))
	int32 FrameDelay{0};
};
