#pragma once

#include "Engine/DataAsset.h"
#include "Utility/AlsGameplayTags.h"
#include "AlsMovementSettings.generated.h"

class UCurveFloat;
class UCurveVector;

USTRUCT(BlueprintType)
struct ALS_API FAlsMovementGaitSettings
{
	GENERATED_BODY()

public:
	// Currently, the direction-dependent movement speed can cause some jitter in multiplayer, so enable it at your own risk.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|移动设置",
		Meta = (DisplayName = "允许方向相关移动速度", ToolTip = "启用后，可为前后方向设置不同移动速度；多人联机下可能产生轻微抖动。"))
	uint8 bAllowDirectionDependentMovementSpeed : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "步行前进速度", ToolTip = "角色步行前进时的最大速度。"))
	float WalkForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s",
		        DisplayName = "步行后退速度", ToolTip = "启用方向相关移动速度时，角色步行后退时的最大速度。"))
	float WalkBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "跑步前进速度", ToolTip = "角色跑步前进时的最大速度。"))
	float RunForwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s",
		        DisplayName = "跑步后退速度", ToolTip = "启用方向相关移动速度时，角色跑步后退时的最大速度。"))
	float RunBackwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "冲刺速度", ToolTip = "角色冲刺时的最大速度。"))
	float SprintSpeed{650.0f};

	// Gait amount to acceleration, deceleration, and ground friction curve.
	// Gait amount ranges from 0 to 3, where 0 is stopped, 1 is walking, 2 is running, and 3 is sprinting.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (DisplayName = "加减速与地面摩擦曲线", ToolTip = "步态强度到加速度、减速度和地面摩擦的映射曲线。"))
	TObjectPtr<UCurveVector> AccelerationAndDecelerationAndGroundFrictionCurve;

	// Gait amount to rotation interpolation speed curve.
	// Gait amount ranges from 0 to 3, where 0 is stopped, 1 is walking, 2 is running, and 3 is sprinting.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (DisplayName = "旋转插值速度曲线", ToolTip = "步态强度到旋转插值速度的映射曲线。"))
	TObjectPtr<UCurveFloat> RotationInterpolationSpeedCurve;

public:
	float GetMaxWalkSpeed() const;

	float GetMaxRunSpeed() const;
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMovementStanceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动设置",
		Meta = (ForceInlineRow, DisplayName = "姿态设置表", ToolTip = "不同姿态对应的步态移动设置表。"))
	TMap<FGameplayTag, FAlsMovementGaitSettings> Stances
	{
		{AlsStanceTags::Standing, {}},
		{AlsStanceTags::Crouching, {}}
	};
};

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsMovementSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	// Range of velocity angle relative to the view direction at which
	// interpolation from forward speed to backward speed will take place.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|移动设置",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "速度角度插值范围",
		        ToolTip = "相对视角的速度角度落在该范围内时，会在前进速度和后退速度之间进行插值。"))
	FFloatInterval VelocityAngleToSpeedInterpolationRange{100.0f, 125.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|移动设置",
		Meta = (ForceInlineRow, DisplayName = "旋转模式设置表", ToolTip = "不同旋转模式下的姿态与步态设置表。"))
	TMap<FGameplayTag, FAlsMovementStanceSettings> RotationModes
	{
		{AlsRotationModeTags::VelocityDirection, {}},
		{AlsRotationModeTags::ViewDirection, {}},
		{AlsRotationModeTags::Aiming, {}}
	};
};

inline float FAlsMovementGaitSettings::GetMaxWalkSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
		       ? FMath::Max(WalkForwardSpeed, WalkBackwardSpeed)
		       : WalkForwardSpeed;
}

inline float FAlsMovementGaitSettings::GetMaxRunSpeed() const
{
	return bAllowDirectionDependentMovementSpeed
		       ? FMath::Max(RunForwardSpeed, RunBackwardSpeed)
		       : RunForwardSpeed;
}
