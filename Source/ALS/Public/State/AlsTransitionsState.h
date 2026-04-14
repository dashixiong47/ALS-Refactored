#pragma once

#include "AlsTransitionsState.generated.h"

class UAnimSequenceBase;

USTRUCT(BlueprintType)
struct ALS_API FAlsTransitionsState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "允许过渡", ToolTip = "当前是否允许执行过渡动画。"))
	uint8 bTransitionsAllowed : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "排队过渡序列", ToolTip = "当前排队等待播放的过渡动画序列。"))
	TObjectPtr<UAnimSequenceBase> QueuedTransitionSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "排队过渡淡入时长", ToolTip = "排队过渡动画的淡入时长。"))
	float QueuedTransitionBlendInDuration{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "排队过渡淡出时长", ToolTip = "排队过渡动画的淡出时长。"))
	float QueuedTransitionBlendOutDuration{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "排队过渡播放速率", ToolTip = "排队过渡动画的播放速率。"))
	float QueuedTransitionPlayRate{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "排队过渡开始时间", ToolTip = "排队过渡动画的开始时间。"))
	float QueuedTransitionStartTime{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "已排队停止过渡", ToolTip = "当前是否已请求停止所有过渡。"))
	uint8 bStopTransitionsQueued : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "停止过渡淡出时长", ToolTip = "停止排队过渡时使用的淡出时长。"))
	float QueuedStopTransitionsBlendOutDuration{-1.0f};
};
