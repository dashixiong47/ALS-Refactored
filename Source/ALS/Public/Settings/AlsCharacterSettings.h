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
	// Actor will be considered as teleported if he has moved farther than this distance in 1 frame.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "传送距离阈值",
		        ToolTip = "单帧位移超过该距离时，角色会被视为发生了传送。"))
	float TeleportDistanceThreshold{50.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "移动速度阈值",
		        ToolTip = "速度高于该值时，ALS 会认为角色处于移动状态。"))
	float MovingSpeedThreshold{50.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "空中旋转模式", ToolTip = "角色在空中时采用的旋转策略。"))
	EAlsInAirRotationMode InAirRotationMode{EAlsInAirRotationMode::RotateToVelocityOnJump};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "允许空中瞄准", ToolTip = "启用后，角色在空中也可以进入瞄准状态。"))
	uint8 bAllowAimingWhenInAir : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "冲刺优先于瞄准", ToolTip = "启用后，冲刺会优先覆盖瞄准状态。"))
	uint8 bSprintHasPriorityOverAiming : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "冲刺时朝速度旋转", ToolTip = "启用后，角色冲刺时会朝速度方向旋转。"))
	uint8 bRotateToVelocityWhenSprinting : 1 {false};

	// If checked, the character will rotate relative to the object it is standing on in the velocity
	// direction rotation mode, otherwise the character will ignore that object and keep its world rotation.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "速度方向模式继承基底旋转",
		        ToolTip = "启用后，速度方向旋转模式下会继承站立物体的旋转；否则保持世界旋转。"))
	uint8 bInheritMovementBaseRotationInVelocityDirectionRotationMode : 1 {false};

	// If checked, the character will rotate towards the direction they want to move, but is not always able to due to obstacles.
	// This setting is only used if the bIgnoreBaseRotation setting from the character movement component is set to true.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "速度方向模式朝期望速度旋转",
		        ToolTip = "启用后，速度方向旋转模式会尽量朝角色期望移动方向旋转。"))
	uint8 bRotateTowardsDesiredVelocityInVelocityDirectionRotationMode : 1 {true};

	// If checked, the character will automatically rotate towards the view direction on any movement input while the actor is not moving.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "静止输入自动朝视角旋转",
		        ToolTip = "启用后，角色静止时只要出现移动输入，就会自动朝视角方向旋转。"))
	uint8 bAutoRotateOnAnyInputWhileNotMovingInViewDirectionRotationMode : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "视角设置", ToolTip = "ALS 视角与视角网络平滑相关设置。"))
	FAlsViewSettings View;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "翻越设置", ToolTip = "ALS 翻越系统的通用设置。"))
	FAlsGeneralMantlingSettings Mantling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "布娃娃设置", ToolTip = "ALS 布娃娃系统相关设置。"))
	FAlsRagdollingSettings Ragdolling;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|角色设置",
		Meta = (DisplayName = "翻滚设置", ToolTip = "ALS 翻滚系统相关设置。"))
	FAlsRollingSettings Rolling;

public:
	UAlsCharacterSettings();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
};
