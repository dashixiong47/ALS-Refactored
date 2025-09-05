#pragma once

#include "AlsRagdollingSettings.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct ALS_API FAlsRagdollingSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="落地时启动布娃娃"))
	uint8 bStartRagdollingOnLand : 1 {true};

	// 当角色落地速度超过指定值时启动布娃娃
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bStartRagdollingOnLand", ForceUnits = "cm/s", DisplayName="落地布娃娃速度阈值"))
	float RagdollingOnLandSpeedThreshold{1000.0f};

	// 如果选中，布娃娃启动后的几帧内速度将受角色最后速度限制
	// 此方法用于防止在不稳定 FPS 下布娃娃获得过高的初始速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="限制初始布娃娃速度"))
	uint8 bLimitInitialRagdollSpeed : 1 {true};

	// 向前翻身动画蒙太奇
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="向前翻身蒙太奇"))
	TObjectPtr<UAnimMontage> GetUpFrontMontage;

	// 向后翻身动画蒙太奇
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="向后翻身蒙太奇"))
	TObjectPtr<UAnimMontage> GetUpBackMontage;

};
