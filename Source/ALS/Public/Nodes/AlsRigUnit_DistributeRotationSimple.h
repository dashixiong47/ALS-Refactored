#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_DistributeRotationSimple.generated.h"

USTRUCT(DisplayName = "简单分配旋转", Meta = (Category = "ALS|控制绑定", NodeColor = "0.0 0.36 1.0"))
struct ALS_API FAlsRigUnit_DistributeRotationSimple : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, DisplayName = "目标骨骼", ToolTip = "需要按顺序分配旋转的元素列表。"))
	TArray<FRigElementKey> Items;

	UPROPERTY(Meta = (Input, DisplayName = "旋转", ToolTip = "要分配到目标骨骼上的总旋转。"))
	FQuat Rotation{ForceInit};

	UPROPERTY(Transient)
	TArray<FCachedRigElement> CachedItems;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
