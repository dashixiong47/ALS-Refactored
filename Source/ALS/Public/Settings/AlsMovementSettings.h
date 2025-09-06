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
	// 当前，基于方向的移动速度在多人游戏中可能会引起抖动，请谨慎启用。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS", DisplayName="允许基于方向的移动速度")
	uint8 bAllowDirectionDependentMovementSpeed : 1 {false};

	// 向前行走速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		DisplayName="行走前进速度", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float WalkForwardSpeed{175.0f};

	// 向后行走速度（仅在允许方向依赖时启用）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		DisplayName="行走后退速度",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float WalkBackwardSpeed{175.0f};

	// 向前奔跑速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		DisplayName="奔跑前进速度", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float RunForwardSpeed{375.0f};

	// 向后奔跑速度（仅在允许方向依赖时启用）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		DisplayName="奔跑后退速度",
		Meta = (ClampMin = 0, EditCondition = "bAllowDirectionDependentMovementSpeed", ForceUnits = "cm/s"))
	float RunBackwardSpeed{375.0f};

	// 冲刺速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		DisplayName="冲刺速度", Meta = (ClampMin = 0, ForceUnits = "cm/s"))
	float SprintSpeed{650.0f};

	// 步态值到加速度、减速度和地面摩擦曲线。
	// 步态值范围：0 = 停止，1 = 行走，2 = 奔跑，3 = 冲刺。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		DisplayName="加减速与摩擦曲线")
	TObjectPtr<UCurveVector> AccelerationAndDecelerationAndGroundFrictionCurve;

	// 步态值到旋转插值速度曲线。
	// 步态值范围：0 = 停止，1 = 行走，2 = 奔跑，3 = 冲刺。
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS",
		DisplayName="旋转插值速度曲线")
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
	// 速度方向相对于视角方向的角度范围，用于前后速度插值
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"), DisplayName = "速度角度插值范围")
	FVector2f VelocityAngleToSpeedInterpolationRange{100.0f, 125.0f};

	// 不同旋转模式下的移动姿态设置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ForceInlineRow), DisplayName = "旋转模式移动姿态映射")
	TMap<FGameplayTag, FAlsMovementStanceSettings> RotationModes
	{
	    {AlsRotationModeTags::VelocityDirection, {}},
		{AlsRotationModeTags::ViewDirection, {}},
		{AlsRotationModeTags::Aiming, {}}
	};


public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
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
