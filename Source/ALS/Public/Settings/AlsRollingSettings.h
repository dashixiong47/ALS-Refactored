#pragma once

#include "AlsRollingSettings.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct ALS_API FAlsRollingSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻滚设置",
		Meta = (DisplayName = "翻滚蒙太奇", ToolTip = "翻滚动作使用的动画蒙太奇。"))
	TObjectPtr<UAnimMontage> Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻滚设置",
		Meta = (DisplayName = "开始时蹲伏", ToolTip = "启用后，翻滚开始时会自动切换为蹲伏姿态。"))
	uint8 bCrouchOnStart : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻滚设置",
		Meta = (DisplayName = "开始时朝输入旋转", ToolTip = "启用后，翻滚开始时会朝输入方向旋转。"))
	uint8 bRotateToInputOnStart : 1 {true};

	// The lower the value, the faster the interpolation. A zero value results in instant interpolation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻滚设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "旋转插值半衰期", ToolTip = "值越小旋转越快，0 表示瞬间完成插值。"))
	float RotationInterpolationHalfLife{0.1f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻滚设置",
		Meta = (DisplayName = "落地开始翻滚", ToolTip = "启用后，落地速度过大时会自动开始翻滚。"))
	uint8 bStartRollingOnLand : 1 {true};

	// Rolling will start if the character lands with a speed greater than the specified value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻滚设置",
		Meta = (ClampMin = 0, EditCondition = "bStartRollingOnLand", ForceUnits = "cm/s",
		        DisplayName = "落地翻滚速度阈值", ToolTip = "落地速度大于该值时会自动开始翻滚。"))
	float RollingOnLandSpeedThreshold{700.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻滚设置",
		Meta = (DisplayName = "空中打断翻滚", ToolTip = "启用后，角色进入空中时会打断当前翻滚。"))
	uint8 bInterruptRollingWhenInAir : 1 {true};
};
