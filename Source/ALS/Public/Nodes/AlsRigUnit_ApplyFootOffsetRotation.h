#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_ApplyFootOffsetRotation.generated.h"

USTRUCT(DisplayName = "应用脚部旋转偏移", Meta = (Category = "ALS|控制绑定", NodeColor = "0.0 0.36 1.0"))
struct ALS_API FAlsRigUnit_ApplyFootOffsetRotation : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "小腿骨骼", ToolTip = "用于计算脚部旋转偏移的小腿元素。"))
	FRigElementKey CalfItem;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "脚骨骼", ToolTip = "用于应用旋转偏移的脚部元素。"))
	FRigElementKey FootItem;

	UPROPERTY(Transient, Meta = (Input, DisplayName = "脚目标旋转", ToolTip = "脚部期望达到的目标旋转。"))
	FQuat FootTargetRotation{ForceInit};

	UPROPERTY(Transient, Meta = (Input, DisplayName = "脚部偏移法线", ToolTip = "地面检测得到的脚部法线方向。"))
	FVector FootOffsetNormal{FVector::UpVector};

	UPROPERTY(Meta = (Input, ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "摆动 1 限制角",
		ToolTip = "脚部在第一摆动轴上的允许旋转范围。"))
	FFloatInterval Swing1LimitAngle{-20.0f, 40.0f};

	UPROPERTY(Meta = (Input, ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "摆动 2 限制角",
		ToolTip = "脚部在第二摆动轴上的允许旋转范围。"))
	FFloatInterval Swing2LimitAngle{-15.0f, 5.0f};

	UPROPERTY(Meta = (Input, ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "扭转限制角",
		ToolTip = "脚部绕自身轴线允许的扭转范围。"))
	FFloatInterval TwistLimitAngle{0.0f, 0.0f};

	// The lower the value, the faster the interpolation. A zero value results in instant interpolation.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s", DisplayName = "偏移插值半衰期",
		ToolTip = "脚部旋转偏移衰减到一半所需的时间。"))
	float OffsetInterpolationHalfLife{0.1f};

	UPROPERTY(Transient)
	bool bInitialized{false};

	UPROPERTY(Transient)
	FCachedRigElement CachedCalfItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedFootItem;

	UPROPERTY(Transient)
	FVector OffsetNormal{FVector::UpVector};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "脚部旋转", ToolTip = "应用偏移后的最终脚部旋转。"))
	FQuat FootRotation{ForceInit};

	UPROPERTY(Transient)
	FQuat FootReferenceLocalRotation{ForceInit};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};
