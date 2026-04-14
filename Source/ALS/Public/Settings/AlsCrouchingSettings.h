#pragma once

#include "AlsCrouchingSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsCrouchingSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|蹲伏设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "动画蹲伏速度", ToolTip = "蹲伏移动动画对应的参考速度。"))
	float AnimatedCrouchSpeed{150.0f};

	// Movement speed to stride blend amount curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|蹲伏设置",
		Meta = (DisplayName = "步幅混合曲线", ToolTip = "移动速度到步幅混合量的映射曲线。"))
	TObjectPtr<UCurveFloat> StrideBlendAmountCurve;
};
