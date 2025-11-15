#pragma once

#include "CoreMinimal.h"
#include "Units/RigUnit.h"
#include "AlsRigUnit_HitReaction.generated.h"

/**
 * Spine 受击旋转（从下到上逐级衰减）
 */
USTRUCT(DisplayName = "Spine Hit Reaction", Meta = (Category = "ALS", NodeColor = "1.0 0.2 0.2"))
struct ALS_API FAlsRigUnit_SpineHitReaction : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	// 脊柱链（从下到上填：spine_01 -> spine_02 -> ... -> head）
	UPROPERTY(meta = (Input))
	TArray<FRigElementKey> SpineChain;

	// 受击方向（世界空间）
	UPROPERTY(meta = (Input))
	FVector HitDirection = FVector::ZeroVector;

	// 受击强度（角度，度数）
	UPROPERTY(meta = (Input))
	float HitStrength = 0.0f;

	// 受击权重（0~1，衰减控制）
	UPROPERTY(meta = (Input))
	float HitAlpha = 0.0f;

	// 定义骨骼坐标系：向上轴
	UPROPERTY(meta = (Input))
	FVector UpAxis = FVector::UpVector;

	// 定义骨骼坐标系：前向轴（Pitch）
	UPROPERTY(meta = (Input))
	FVector ForwardAxis = FVector::ForwardVector;

	UPROPERTY(Transient)
	TArray<FCachedRigElement> CachedSpine;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
