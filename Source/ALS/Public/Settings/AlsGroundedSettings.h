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

	// 速度混合插值速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="速度混合插值速度")
	float VelocityBlendInterpolationSpeed{12.0f};

};
