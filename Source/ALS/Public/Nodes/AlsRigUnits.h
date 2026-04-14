#pragma once

#include "RigVMFunctions/RigVMFunction_ControlFlow.h"
#include "RigVMFunctions/Math/RigVMFunction_MathFloat.h"
#include "RigVMFunctions/Simulation/RigVMFunction_SimBase.h"
#include "Units/RigUnit.h"
#include "AlsRigUnits.generated.h"

USTRUCT(DisplayName = "钳制到 01", Meta = (Category = "ALS|控制绑定"))
struct ALS_API FAlsRigVMFunction_Clamp01Float : public FRigVMFunction_MathFloatBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, DisplayName = "数值", ToolTip = "待钳制到 0 到 1 范围内的输入值。"))
	float Value{0.0f};

	UPROPERTY(Meta = (Output, DisplayName = "结果", ToolTip = "钳制后的结果值。"))
	float Result{0.0f};

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};

USTRUCT(DisplayName = "精确阻尼（向量）", Meta = (Category = "ALS|控制绑定"))
struct ALS_API FAlsRigVMFunction_DamperExactVector : public FRigVMFunction_SimBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, DisplayName = "目标", ToolTip = "当前向量将平滑逼近的目标值。"))
	FVector Target{ForceInit};

	// HalfLife is the time it takes for the distance to the target to be reduced by half.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s", DisplayName = "半衰期",
		ToolTip = "当前值与目标值的差距衰减到一半所需的时间。"))
	float HalfLife{1.0f};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "当前值", ToolTip = "经过阻尼计算后的当前向量。"))
	FVector Current{ForceInit};

	UPROPERTY(Transient)
	bool bInitialized{false};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

USTRUCT(DisplayName = "精确阻尼（四元数）", Meta = (Category = "ALS|控制绑定"))
struct ALS_API FAlsRigVMFunction_DamperExactQuaternion : public FRigVMFunction_SimBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, DisplayName = "目标", ToolTip = "当前旋转将平滑逼近的目标四元数。"))
	FQuat Target{ForceInit};

	// HalfLife is the time it takes for the distance to the target to be reduced by half.
	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "s", DisplayName = "半衰期",
		ToolTip = "当前旋转与目标旋转的差距衰减到一半所需的时间。"))
	float HalfLife{1.0f};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "当前值", ToolTip = "经过阻尼计算后的当前旋转。"))
	FQuat Current{ForceInit};

	UPROPERTY(Transient)
	bool bInitialized{false};

public:
	virtual void Initialize() override;

	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

// Calculates the projection location and direction of the perpendicular to AC through B.
USTRUCT(DisplayName = "计算极向量", Meta = (Category = "ALS|控制绑定", NodeColor = "0.05 0.25 0.05"))
struct ALS_API FAlsRigUnit_CalculatePoleVector : public FRigUnit
{
	GENERATED_BODY()

public:
	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "元素 A", ToolTip = "用于计算极向量的第一个元素。"))
	FRigElementKey ItemA;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "元素 B", ToolTip = "用于计算极向量的中间元素。"))
	FRigElementKey ItemB;

	UPROPERTY(Meta = (Input, ExpandByDefault, DisplayName = "元素 C", ToolTip = "用于计算极向量的第三个元素。"))
	FRigElementKey ItemC;

	UPROPERTY(Meta = (Input, DisplayName = "使用初始姿态", ToolTip = "是否基于初始姿态而不是当前姿态读取元素位置。"))
	bool bInitial{false};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "成功", ToolTip = "本次极向量计算是否成功。"))
	bool bSuccess{false};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "元素 B 位置", ToolTip = "元素 B 的当前位置。"))
	FVector ItemBLocation{ForceInit};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "元素 B 投影位置",
		ToolTip = "元素 B 在 AC 连线垂线投影上的位置。"))
	FVector ItemBProjectionLocation{ForceInit};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "极向量方向", ToolTip = "从投影点指向元素 B 的极向量方向。"))
	FVector PoleDirection{FVector::ForwardVector};

	UPROPERTY(Transient)
	FCachedRigElement CachedItemA;

	UPROPERTY(Transient)
	FCachedRigElement CachedItemB;

	UPROPERTY(Transient)
	FCachedRigElement CachedItemC;

public:
	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;
};

USTRUCT(DisplayName = "是否为游戏世界", Meta = (Category = "ALS|控制绑定"))
struct ALS_API FAlsRigVMFunction_IsGameWorld : public FRigVMFunction_ControlFlowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, Meta = (Input, DisplayName = "执行", ToolTip = "控制流输入执行引脚。"))
	FRigVMExecuteContext ExecuteContext;

	UPROPERTY(Transient, Meta = (Output, DisplayName = "是", ToolTip = "当前运行环境是游戏世界时输出。"))
	FRigVMExecuteContext True;

	UPROPERTY(Transient, Meta = (Output, DisplayName = "否", ToolTip = "当前运行环境不是游戏世界时输出。"))
	FRigVMExecuteContext False;

	UPROPERTY(Meta = (Output, DisplayName = "完成", ToolTip = "控制流执行结束后输出。"))
	FRigVMExecuteContext Completed;

	UPROPERTY(Transient, Meta = (Singleton))
	FName BlockToRun;

public:
	RIGVM_METHOD()
	// ReSharper disable once CppFunctionIsNotImplemented
	virtual void Execute() override;

	virtual const TArray<FName>& GetControlFlowBlocks_Impl() const override;
};
