#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_ChainLength.generated.h"

USTRUCT(DisplayName = "骨链长度", Meta = (Category = "ALS|控制绑定", NodeColor = "0.05 0.25 0.05"))
struct ALS_API FAlsRigUnit_ChainLength : public FRigUnit
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "祖先骨骼", ToolTip = "骨链起点元素。"))
	FRigElementKey AncestorItem;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "后代骨骼", ToolTip = "骨链终点元素。"))
	FRigElementKey DescendantItem;

	UPROPERTY(Meta = (Input, DisplayName = "使用初始姿态", ToolTip = "是否基于初始姿态而不是当前姿态计算骨链长度。"))
	bool bInitial{false};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "长度", ToolTip = "祖先元素到后代元素之间的骨链总长度。"))
	float Length{0.0f};

	UPROPERTY(Transient)
	FCachedRigElement CachedAncestorItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedDescendantItem;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
