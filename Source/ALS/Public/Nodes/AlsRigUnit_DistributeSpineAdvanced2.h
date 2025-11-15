#pragma once

#include "CoreMinimal.h"
#include "Units/RigUnit.h"
#include "AlsRigUnit_DistributeSpineAdvanced2.generated.h"

/**
 * 分配脊柱旋转（Yaw 单骨骼 + Pitch 上下分骨骼控制，可开关）
 */
USTRUCT(DisplayName = "Distribute Spine Advanced2", Meta = (Category = "ALS", NodeColor = "0.0 0.6 1.0"))
struct ALS_API FAlsRigUnit_DistributeSpineAdvanced2 : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	// 左右旋转（Yaw）的骨骼（只允许一个）
	UPROPERTY(meta = (Input))
	FRigElementKey SpineYawBone;

	// 向上看时使用的脊柱骨骼
	UPROPERTY(meta = (Input))
	TArray<FRigElementKey> SpinePitchUpBones;

	// 向上看的权重
	UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	TArray<float> SpinePitchUpWeights;

	// 向下看时使用的脊柱骨骼
	UPROPERTY(meta = (Input))
	TArray<FRigElementKey> SpinePitchDownBones;

	// 向下看的权重
	UPROPERTY(meta = (Input, ClampMin = "0.0", ClampMax = "1.0", UIMin = "0.0", UIMax = "1.0"))
	TArray<float> SpinePitchDownWeights;

	// 左右看角度（Yaw，度数）
	UPROPERTY(meta = (Input))
	float YawAngle{0.0f};

	// 上下看角度（Pitch，度数）
	UPROPERTY(meta = (Input))
	float PitchAngle{0.0f};

	// 是否启用上下旋转
	UPROPERTY(meta = (Input))
	bool bEnablePitchRotation{true};

	UPROPERTY(Transient)
	FCachedRigElement CachedSpineYawBone;

	UPROPERTY(Transient)
	TArray<FCachedRigElement> CachedSpinePitchUpBones;

	UPROPERTY(Transient)
	TArray<FCachedRigElement> CachedSpinePitchDownBones;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
