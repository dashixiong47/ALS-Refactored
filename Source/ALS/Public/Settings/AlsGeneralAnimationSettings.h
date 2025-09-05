#pragma once

#include "AlsGeneralAnimationSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsGeneralAnimationSettings
{
	GENERATED_BODY()

	// 是否使用手部 IK 骨骼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="使用手部IK骨骼")
	uint8 bUseHandIkBones : 1 {true};

	// 是否使用脚部 IK 骨骼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="使用脚部IK骨骼")
	uint8 bUseFootIkBones : 1 {true};

	// 移动平滑速度阈值（cm/s）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s"), DisplayName="移动平滑速度阈值")
	float MovingSmoothSpeedThreshold{150.0f};

	// 倾斜插值速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="倾斜插值速度")
	float LeanInterpolationSpeed{4.0f};

};
