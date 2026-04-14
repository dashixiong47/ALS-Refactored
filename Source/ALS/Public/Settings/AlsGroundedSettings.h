#pragma once

#include "AlsGroundedSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsGroundedSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|地面设置",
		Meta = (DisplayName = "前向偏航偏移曲线", ToolTip = "前向移动时使用的旋转偏航偏移曲线。"))
	TObjectPtr<UCurveFloat> RotationYawOffsetForwardCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|地面设置",
		Meta = (DisplayName = "后向偏航偏移曲线", ToolTip = "后向移动时使用的旋转偏航偏移曲线。"))
	TObjectPtr<UCurveFloat> RotationYawOffsetBackwardCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|地面设置",
		Meta = (DisplayName = "左向偏航偏移曲线", ToolTip = "左向移动时使用的旋转偏航偏移曲线。"))
	TObjectPtr<UCurveFloat> RotationYawOffsetLeftCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|地面设置",
		Meta = (DisplayName = "右向偏航偏移曲线", ToolTip = "右向移动时使用的旋转偏航偏移曲线。"))
	TObjectPtr<UCurveFloat> RotationYawOffsetRightCurve;

	// The lower the value, the faster the interpolation. A zero value results in instant interpolation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|地面设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "速度混合插值半衰期", ToolTip = "值越小速度混合插值越快，0 表示瞬间完成插值。"))
	float VelocityBlendInterpolationHalfLife{0.1f};
};
