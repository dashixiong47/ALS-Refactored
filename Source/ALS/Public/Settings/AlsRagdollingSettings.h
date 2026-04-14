#pragma once

#include "AlsRagdollingSettings.generated.h"

class UAnimMontage;

USTRUCT(BlueprintType)
struct ALS_API FAlsRagdollingSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|布娃娃设置",
		Meta = (DisplayName = "落地开始布娃娃", ToolTip = "启用后，角色落地速度过大时会自动进入布娃娃。"))
	uint8 bStartRagdollingOnLand : 1 {true};

	// Ragdolling will start if the character lands with a speed greater than the specified value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|布娃娃设置",
		Meta = (ClampMin = 0, EditCondition = "bStartRagdollingOnLand", ForceUnits = "cm/s",
		        DisplayName = "落地布娃娃速度阈值", ToolTip = "落地速度大于该值时会自动进入布娃娃。"))
	float RagdollingOnLandSpeedThreshold{1000.0f};

	// If checked, the ragdoll's speed will be limited by the character's last speed for a few frames
	// after activation. This hack is used to prevent the ragdoll from getting a very high initial speed
	// at unstable FPS, which can be reproduced by jumping and activating the ragdoll at the same time.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|布娃娃设置",
		Meta = (DisplayName = "限制初始布娃娃速度", ToolTip = "启用后，刚进入布娃娃的前几帧会限制速度，避免不稳定帧率下初速异常过高。"))
	uint8 bLimitInitialRagdollSpeed : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|布娃娃设置",
		Meta = (DisplayName = "正面起身蒙太奇", ToolTip = "角色仰躺时使用的起身蒙太奇。"))
	TObjectPtr<UAnimMontage> GetUpFrontMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|布娃娃设置",
		Meta = (DisplayName = "背面起身蒙太奇", ToolTip = "角色俯卧时使用的起身蒙太奇。"))
	TObjectPtr<UAnimMontage> GetUpBackMontage;
};
