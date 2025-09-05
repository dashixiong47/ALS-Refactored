#pragma once

#include "AlsStandingSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsStandingSettings
{
	GENERATED_BODY()

	// 行走动画速度（厘米/秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"), DisplayName="行走动画速度")
	float AnimatedWalkSpeed{150.0f};

	// 奔跑动画速度（厘米/秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"), DisplayName="奔跑动画速度")
	float AnimatedRunSpeed{350.0f};

	// 冲刺动画速度（厘米/秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"), DisplayName="冲刺动画速度")
	float AnimatedSprintSpeed{600.0f};

	// 行走步幅混合曲线（速度 → 步幅混合值）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="行走步幅混合曲线")
	TObjectPtr<UCurveFloat> StrideBlendAmountWalkCurve;

	// 奔跑步幅混合曲线（速度 → 步幅混合值）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="奔跑步幅混合曲线")
	TObjectPtr<UCurveFloat> StrideBlendAmountRunCurve;

	// 触发转向动作的最小速度阈值（厘米/秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"), DisplayName="转向触发速度阈值")
	float PivotActivationSpeedThreshold{200.0f};

};
