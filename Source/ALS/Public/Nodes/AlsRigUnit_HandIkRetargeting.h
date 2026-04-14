#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_HandIkRetargeting.generated.h"

USTRUCT(DisplayName = "手部 IK 重定向", Meta = (Category = "ALS|控制绑定", NodeColor = "0.0 0.36 1.0"))
struct ALS_API FAlsRigUnit_HandIkRetargeting : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "左手骨骼", ToolTip = "左手原始骨骼元素。"))
	FRigElementKey LeftHandItem;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "左手 IK", ToolTip = "左手 IK 控制元素。"))
	FRigElementKey LeftHandIkItem;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "右手骨骼", ToolTip = "右手原始骨骼元素。"))
	FRigElementKey RightHandItem;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "右手 IK", ToolTip = "右手 IK 控制元素。"))
	FRigElementKey RightHandIkItem;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "需要移动的骨骼", ToolTip = "会跟随重定向结果一起移动的元素列表。"))
	TArray<FRigElementKey> ItemsToMove;

	// Which hand to favor. 0.5 is equal weight for both, 1 - right hand, 0 - left hand.
	UPROPERTY(Meta = (Input, DisplayName = "重定向权重", ToolTip = "左右手之间的偏向权重，0 为左手，1 为右手。"))
	float RetargetingWeight{0.5f};

	UPROPERTY(Meta = (Input, DisplayName = "生效权重", ToolTip = "本次手部 IK 重定向的整体权重。"))
	float Weight{1.0f};

	UPROPERTY(Meta = (Input, Constant, DisplayName = "同步到子级", ToolTip = "是否将位移继续传递到子级元素。"))
	bool bPropagateToChildren{false};

	UPROPERTY(Transient)
	FCachedRigElement CachedLeftHandItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedLeftHandIkItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedRightHandItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedRightHandIkItem;

	UPROPERTY(Transient)
	TArray<FCachedRigElement> CachedItemsToMove;

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
