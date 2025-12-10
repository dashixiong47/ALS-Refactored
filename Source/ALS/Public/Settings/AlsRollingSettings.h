#pragma once

#include "AlsRollingSettings.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct ALS_API FAlsRollingSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (DisplayName = "翻滚蒙太奇"))
	TObjectPtr<UAnimMontage> Montage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (DisplayName = "开始时下蹲"))
	uint8 bCrouchOnStart : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (DisplayName = "开始时朝输入旋转"))
	uint8 bRotateToInputOnStart : 1 {true};

	// 该值越小，插值越快。零值表示瞬间插值。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "旋转插值半衰期"))
	float RotationInterpolationHalfLife{0.1f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (DisplayName = "着陆时开始翻滚"))
	uint8 bStartRollingOnLand : 1 {true};

	// 如果角色以大于指定速度着陆，则开始翻滚。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bStartRollingOnLand", ForceUnits = "cm/s", DisplayName = "着陆翻滚速度阈值"))
	float RollingOnLandSpeedThreshold{700.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (DisplayName = "在空中中断翻滚"))
	uint8 bInterruptRollingWhenInAir : 1 {true};
};