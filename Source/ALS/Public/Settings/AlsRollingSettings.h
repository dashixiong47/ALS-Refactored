#pragma once

#include "AlsRollingSettings.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct ALS_API FAlsRollingSettings
{
	GENERATED_BODY()

	// 翻滚蒙太奇
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="翻滚蒙太奇"))
	TObjectPtr<UAnimMontage> Montage;

	// 开始时角色是否下蹲
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="开始时下蹲"))
	uint8 bCrouchOnStart : 1 {true};

	// 开始时是否根据输入方向旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="开始时旋转至输入方向"))
	uint8 bRotateToInputOnStart : 1 {true};

	// 旋转插值速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, DisplayName="旋转插值速度"))
	float RotationInterpolationSpeed{10.0f};

	// 落地时是否启动翻滚
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="落地时启动翻滚"))
	uint8 bStartRollingOnLand : 1 {true};

	// 当角色落地速度超过指定值时启动翻滚
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bStartRollingOnLand", ForceUnits = "cm/s", DisplayName="落地翻滚速度阈值"))
	float RollingOnLandSpeedThreshold{700.0f};

	// 在空中时是否中断翻滚
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="空中中断翻滚"))
	uint8 bInterruptRollingWhenInAir : 1 {true};

};
