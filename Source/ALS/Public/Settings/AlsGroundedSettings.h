#pragma once

#include "AlsGroundedSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsGroundedSettings
{
	GENERATED_BODY()

	// 前向旋转偏航曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="前向旋转偏航曲线")
	TObjectPtr<UCurveFloat> RotationYawOffsetForwardCurve;

	// 后向旋转偏航曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="后向旋转偏航曲线")
	TObjectPtr<UCurveFloat> RotationYawOffsetBackwardCurve;

	// 左向旋转偏航曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="左向旋转偏航曲线")
	TObjectPtr<UCurveFloat> RotationYawOffsetLeftCurve;

	// 右向旋转偏航曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="右向旋转偏航曲线")
	TObjectPtr<UCurveFloat> RotationYawOffsetRightCurve;

	// The lower the value, the faster the interpolation. A zero value results in instant interpolation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"))
	float VelocityBlendInterpolationHalfLife{0.1f};
};
