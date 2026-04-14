#pragma once

#include "AlsTransitionsSettings.generated.h"

class UAnimSequenceBase;

USTRUCT(BlueprintType)
struct ALS_API FAlsTransitionsSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "快速停止淡入时长", ToolTip = "快速停止动画的淡入时长。"))
	float QuickStopBlendInDuration{0.1f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "快速停止淡出时长", ToolTip = "快速停止动画的淡出时长。"))
	float QuickStopBlendOutDuration{0.2f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (ClampMin = 0, DisplayName = "快速停止播放速率", ToolTip = "快速停止动画的播放速率范围。"))
	FVector2f QuickStopPlayRate{1.75f, 3.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "快速停止开始时间", ToolTip = "快速停止动画开始播放的时间点。"))
	float QuickStopStartTime{0.3f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (DisplayName = "站立左侧序列", ToolTip = "站立状态左侧快速停止使用的动画序列。"))
	TObjectPtr<UAnimSequenceBase> StandingLeftSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (DisplayName = "站立右侧序列", ToolTip = "站立状态右侧快速停止使用的动画序列。"))
	TObjectPtr<UAnimSequenceBase> StandingRightSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (DisplayName = "蹲伏左侧序列", ToolTip = "蹲伏状态左侧快速停止使用的动画序列。"))
	TObjectPtr<UAnimSequenceBase> CrouchingLeftSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|过渡设置",
		Meta = (DisplayName = "蹲伏右侧序列", ToolTip = "蹲伏状态右侧快速停止使用的动画序列。"))
	TObjectPtr<UAnimSequenceBase> CrouchingRightSequence;
};
