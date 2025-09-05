#pragma once

#include "AlsInAirRotationMode.h"
#include "AlsMantlingSettings.h"
#include "AlsRagdollingSettings.h"
#include "AlsRollingSettings.h"
#include "AlsViewSettings.h"
#include "AlsCharacterSettings.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsCharacterSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	// 移动速度阈值（cm/s）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, ForceUnits = "cm/s"), DisplayName="移动速度阈值")
	float MovingSpeedThreshold{50.0f};

	// 空中旋转模式
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="空中旋转模式")
	EAlsInAirRotationMode InAirRotationMode{EAlsInAirRotationMode::RotateToVelocityOnJump};

	// 是否允许空中瞄准
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="空中允许瞄准")
	uint8 bAllowAimingWhenInAir : 1 {true};

	// 冲刺是否优先于瞄准
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="冲刺优先于瞄准")
	uint8 bSprintHasPriorityOverAiming : 1 {false};

	// 冲刺时是否旋转朝向速度方向
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="冲刺时旋转至速度方向")
	uint8 bRotateToVelocityWhenSprinting : 1 {false};

	// 是否继承角色站立物体的旋转（速度方向模式下）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="继承站立物体旋转（速度方向模式）")
	uint8 bInheritMovementBaseRotationInVelocityDirectionRotationMode : 1 {false};

	// 是否旋转朝向期望的移动方向（速度方向模式下，可能受障碍限制）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="旋转朝向期望移动方向（速度方向模式）")
	uint8 bRotateTowardsDesiredVelocityInVelocityDirectionRotationMode : 1 {true};

	// 是否在未移动时自动朝向视角方向旋转（有移动输入时）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="未移动时自动朝向视角方向旋转")
	uint8 bAutoRotateOnAnyInputWhileNotMovingInViewDirectionRotationMode : 1 {true};

	// 视角设置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="视角设置")
	FAlsViewSettings View;

	// 抬高攀爬设置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="攀爬设置")
	FAlsGeneralMantlingSettings Mantling;

	// 布娃娃设置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="布娃娃设置")
	FAlsRagdollingSettings Ragdolling;

	// 翻滚设置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="翻滚设置")
	FAlsRollingSettings Rolling;


public:
	UAlsCharacterSettings();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
};
