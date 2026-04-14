#pragma once

#include "AlsTurnInPlaceState.generated.h"

class UAlsTurnInPlaceSettings;

USTRUCT(BlueprintType)
struct ALS_API FAlsTurnInPlaceState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "本帧已更新", ToolTip = "当前转身状态是否已在本帧更新。"))
	uint8 bUpdatedThisFrame : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ForceUnits = "s", DisplayName = "激活延迟", ToolTip = "距离真正触发转身还剩余的延迟时间。"))
	float ActivationDelay{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "排队设置", ToolTip = "当前排队等待使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> QueuedSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "排队槽位名称", ToolTip = "当前排队转身使用的动画槽位名称。"))
	FName QueuedSlotName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "排队转身角度", ToolTip = "当前排队转身的目标角度。"))
	float QueuedTurnYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "播放速率", ToolTip = "当前转身动画的播放速率。"))
	float PlayRate{1.0f};
};
