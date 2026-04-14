#pragma once

#include "AlsRotateInPlaceState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsRotateInPlaceState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "本帧已更新", ToolTip = "当前原地旋转状态是否已在本帧更新。"))
	uint8 bUpdatedThisFrame : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "正在向左旋转", ToolTip = "当前是否处于向左原地旋转。"))
	uint8 bRotatingLeft : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "正在向右旋转", ToolTip = "当前是否处于向右原地旋转。"))
	uint8 bRotatingRight : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "播放速率", ToolTip = "当前原地旋转动画的播放速率。"))
	float PlayRate{1.0f};
};
