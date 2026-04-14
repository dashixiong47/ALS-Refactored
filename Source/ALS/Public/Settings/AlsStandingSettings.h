#pragma once

#include "AlsStandingSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsStandingSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|站立设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "动画步行速度", ToolTip = "站立步行动画的参考速度。"))
	float AnimatedWalkSpeed{150.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|站立设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "动画跑步速度", ToolTip = "站立跑步动画的参考速度。"))
	float AnimatedRunSpeed{350.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|站立设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "动画冲刺速度", ToolTip = "站立冲刺动画的参考速度。"))
	float AnimatedSprintSpeed{600.0f};

	// Movement speed to stride blend amount curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|站立设置",
		Meta = (DisplayName = "步行步幅混合曲线", ToolTip = "步行速度到步幅混合量的映射曲线。"))
	TObjectPtr<UCurveFloat> StrideBlendAmountWalkCurve;

	// Movement speed to stride blend amount curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|站立设置",
		Meta = (DisplayName = "跑步步幅混合曲线", ToolTip = "跑步速度到步幅混合量的映射曲线。"))
	TObjectPtr<UCurveFloat> StrideBlendAmountRunCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|站立设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "轴点激活速度阈值", ToolTip = "速度高于该值时允许激活 Pivot 相关表现。"))
	float PivotActivationSpeedThreshold{200.0f};
};
