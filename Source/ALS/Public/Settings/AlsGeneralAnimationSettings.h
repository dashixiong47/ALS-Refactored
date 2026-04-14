#pragma once

#include "AlsGeneralAnimationSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsGeneralAnimationSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|通用动画设置",
		Meta = (DisplayName = "使用手 IK 骨", ToolTip = "启用后，Control Rig 会使用手部 IK 骨。"))
	uint8 bUseHandIkBones : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|通用动画设置",
		Meta = (DisplayName = "使用脚 IK 骨", ToolTip = "启用后，Control Rig 会使用脚部 IK 骨。"))
	uint8 bUseFootIkBones : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|通用动画设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "平滑移动速度阈值", ToolTip = "速度高于该值时，会按平滑移动状态处理动画。"))
	float MovingSmoothSpeedThreshold{150.0f};

	// The lower the value, the faster the interpolation. A zero value results in instant interpolation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|通用动画设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "倾斜插值半衰期", ToolTip = "值越小倾斜插值越快，0 表示瞬间完成插值。"))
	float LeanInterpolationHalfLife{0.2f};
};
