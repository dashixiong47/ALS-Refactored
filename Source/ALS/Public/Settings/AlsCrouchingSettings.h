#pragma once

#include "AlsCrouchingSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsCrouchingSettings
{
	GENERATED_BODY()

	// 蹲伏动画速度（厘米/秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"), DisplayName="蹲伏动画速度")
	float AnimatedCrouchSpeed{150.0f};

	// 步幅混合曲线（速度 → 步幅混合值）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="步幅混合曲线")
	TObjectPtr<UCurveFloat> StrideBlendAmountCurve;

};
