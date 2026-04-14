#pragma once

#include "AlsHeadSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsHeadSettings
{
	GENERATED_BODY()

	// The lower the value, the faster the interpolation. A zero value results in instant interpolation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|头部设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "俯仰插值半衰期", ToolTip = "值越小头部俯仰插值越快，0 表示瞬间完成插值。"))
	float PitchAngleInterpolationHalfLife{0.1f};

	// The lower the value, the faster the interpolation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|头部设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "偏航插值平滑时间", ToolTip = "值越小头部偏航插值越快。"))
	float YawAngleInterpolationSmoothingTime{0.14f};

	// The lower the value, the faster the interpolation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|头部设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "切换左右观察平滑时间", ToolTip = "切换左右观察方向时头部偏航的平滑时间。"))
	float SwitchLookSidesYawAngleInterpolationSmoothingTime{0.28f};
};
