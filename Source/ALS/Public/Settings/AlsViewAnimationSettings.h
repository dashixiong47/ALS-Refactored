#pragma once

#include "AlsViewAnimationSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsViewAnimationSettings
{
	GENERATED_BODY()

	// 面向摄像机的旋转插值速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="面向摄像机旋转插值速度")
	float LookTowardsCameraRotationInterpolationSpeed{8.0f};

	// 面向输入偏航角的旋转插值速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="面向输入偏航角旋转插值速度")
	float LookTowardsInputYawAngleInterpolationSpeed{8.0f};

};
