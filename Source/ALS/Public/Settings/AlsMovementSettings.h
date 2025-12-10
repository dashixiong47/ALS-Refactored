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
	// 当前，基于方向的移动速度可能在多人游戏中导致抖动，启用请自行承担风险。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS", Meta = (DisplayName = "允许基于方向的移动速度"))
	uint8 bAllowDirectionDependentMovementSpeed : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "向前行走速度"))
	float WalkForwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s", DisplayName = "向后行走速度"))
	float WalkBackwardSpeed{175.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "向前跑步速度"))
	float RunForwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s", DisplayName = "向后跑步速度"))
	float RunBackwardSpeed{375.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "冲刺速度"))
	float SprintSpeed{650.0f};

	// 步态值到加速度、减速度和地面摩擦的曲线。
	// 步态值范围为 0 到 3，0 表示静止，1 表示行走，2 表示跑步，3 表示冲刺。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (DisplayName = "加速/减速/地面摩擦 曲线"))
	TObjectPtr<UCurveVector> AccelerationAndDecelerationAndGroundFrictionCurve;

	// 步态值到旋转插值速度的曲线。
	// 步态值范围为 0 到 3，0 表示静止，1 表示行走，2 表示跑步，3 表示冲刺。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (DisplayName = "旋转插值速度 曲线"))
	TObjectPtr<UCurveFloat> RotationInterpolationSpeedCurve;

public:
	float GetMaxWalkSpeed() const;

	float GetMaxRunSpeed() const;
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMovementStanceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceInlineRow))
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
	// 速度方向相对于视角的角度范围。在该范围内会从前向速度插值到后向速度（单位：度）。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName = "速度角度插值范围", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"))
	FFloatInterval VelocityAngleToSpeedInterpolationRange{100.0f, 125.0f};

	// 不同旋转模式对应的站姿设置映射（例如：速度方向、视角、瞄准）。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName = "旋转模式", Meta = (ForceInlineRow))
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
