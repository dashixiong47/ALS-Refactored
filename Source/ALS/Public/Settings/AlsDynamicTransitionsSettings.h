#pragma once

#include "AlsDynamicTransitionsSettings.generated.h"

class UAnimSequenceBase;

USTRUCT(BlueprintType)
struct ALS_API FAlsDynamicTransitionsSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动态过渡设置",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "脚锁距离阈值", ToolTip = "触发动态过渡时使用的脚锁距离阈值。"))
	float FootLockDistanceThreshold{8.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动态过渡设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "混合时长", ToolTip = "动态过渡动画的混合时长。"))
	float BlendDuration{0.2f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动态过渡设置",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "播放速率", ToolTip = "动态过渡动画的播放速率。"))
	float PlayRate{1.5f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动态过渡设置",
		Meta = (DisplayName = "站立左侧序列", ToolTip = "站立状态左脚主导时使用的动态过渡序列。"))
	TObjectPtr<UAnimSequenceBase> StandingLeftSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动态过渡设置",
		Meta = (DisplayName = "站立右侧序列", ToolTip = "站立状态右脚主导时使用的动态过渡序列。"))
	TObjectPtr<UAnimSequenceBase> StandingRightSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动态过渡设置",
		Meta = (DisplayName = "蹲伏左侧序列", ToolTip = "蹲伏状态左脚主导时使用的动态过渡序列。"))
	TObjectPtr<UAnimSequenceBase> CrouchingLeftSequence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动态过渡设置",
		Meta = (DisplayName = "蹲伏右侧序列", ToolTip = "蹲伏状态右脚主导时使用的动态过渡序列。"))
	TObjectPtr<UAnimSequenceBase> CrouchingRightSequence;
};
