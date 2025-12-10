#pragma once

#include "AlsHeadSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsHeadSettings
{
	GENERATED_BODY()

	// 值越低，插值越快。零表示瞬时插值。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName="俯仰角插值半衰期")
	float PitchAngleInterpolationHalfLife{0.1f};

	// 值越低，插值越快。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName="偏航角插值平滑时间")
	float YawAngleInterpolationSmoothingTime{0.14f};

	// 值越低，插值越快。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName="切换注视侧偏航插值平滑时间")
	float SwitchLookSidesYawAngleInterpolationSmoothingTime{0.28f};
};