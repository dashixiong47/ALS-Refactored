#pragma once

#include "Units/RigUnit.h"
#include "Utility/AlsMath.h"
#include "AlsRigUnit_ApplyFootOffsetLocation.generated.h"

USTRUCT(DisplayName = "应用脚部位置偏移", Meta = (Category = "ALS|控制绑定", NodeColor = "0.0 0.36 1.0"))
struct ALS_API FAlsRigUnit_ApplyFootOffsetLocation : public FRigUnitMutable
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "骨盆骨骼", ToolTip = "用于应用脚部位置偏移的骨盆元素。"))
	FRigElementKey PelvisItem;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "大腿骨骼", ToolTip = "用于估算腿长和方向的大腿元素。"))
	FRigElementKey ThighItem;

	UPROPERTY(Transient, Meta = (Input, DisplayName = "脚目标位置", ToolTip = "脚部期望到达的目标位置。"))
	FVector FootTargetLocation{ForceInit};

	UPROPERTY(Transient, Meta = (Input, DisplayName = "脚部 Z 偏移", ToolTip = "地面检测得到的脚部垂直偏移量。"))
	float FootOffsetLocationZ{0.0f};

	UPROPERTY(Transient, Meta = (Input, DisplayName = "骨盆偏移", ToolTip = "当前施加到骨盆上的垂直偏移量。"))
	float PelvisOffset{0.0f};

	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm", DisplayName = "腿长",
		ToolTip = "从大腿到脚部的参考腿长。"))
	float LegLength{0.0f};

	// This limits how high the foot offset can raise the foot relative to the pelvis.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm", DisplayName = "骨盆到脚最小高度",
		ToolTip = "限制脚部相对骨盆可抬高的最小垂直距离。"))
	float MinPelvisToFootDistanceZ{50.0f};

	// Used to prevent the leg from being fully straightened.
	UPROPERTY(Meta = (Input, ClampMin = 0.01, ForceUnits = "x", DisplayName = "最大腿部拉伸比例",
		ToolTip = "限制腿部最大伸长比例，避免完全拉直。"))
	float MaxLegStretchRatio{0.99f};

	// Determines how hard the spring pulls towards the target. The value
	// represents the frequency at which it oscillates when there is no damping.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "hz", DisplayName = "偏移插值频率",
		ToolTip = "脚部偏移弹簧逼近目标时的震荡频率。"))
	float OffsetInterpolationFrequency{12.0};

	// If the value is less than 1, the spring will oscillate before stabilizing on the target.
	// If the value is equal to 1, the spring will reach the target without overshooting.
	// If the value is greater than 1, the spring will take longer to reach the target.
	UPROPERTY(Meta = (Input, ClampMin = 0, DisplayName = "偏移插值阻尼比",
		ToolTip = "控制脚部偏移弹簧的阻尼强度。"))
	float OffsetInterpolationDampingRatio{2.0f};

	// The amount of velocity that will be passed to the spring. A value of 1 will result in a more responsive output, but
	// if the input is noisy or has step changes, these discontinuities will be more noticeable than with a lower value.
	UPROPERTY(Meta = (Input, ClampMin = 0, ClampMax = 1, DisplayName = "目标速度参与量",
		ToolTip = "输入目标速度参与弹簧计算的比例。"))
	float OffsetInterpolationTargetVelocityAmount{0.0f};

	UPROPERTY(Transient)
	bool bInitialized{false};

	UPROPERTY(Transient)
	FCachedRigElement CachedPelvisItem;

	UPROPERTY(Transient)
	FCachedRigElement CachedThighItem;

	UPROPERTY(Transient)
	FAlsSpringFloatState OffsetSpringState;

	UPROPERTY(Transient)
	float OffsetLocationZ{0.0f};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "脚部位置", ToolTip = "应用偏移后的最终脚部位置。"))
	FVector FootLocation{ForceInit};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};
