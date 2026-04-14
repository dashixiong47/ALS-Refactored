#pragma once

#include "AlsLocomotionState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsLocomotionState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "有输入", ToolTip = "当前是否存在有效移动输入。"))
	uint8 bHasInput : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "输入偏航角", ToolTip = "当前输入方向对应的偏航角。"))
	float InputYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "有速度", ToolTip = "当前是否存在有效移动速度。"))
	uint8 bHasVelocity : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "cm/s", DisplayName = "速度", ToolTip = "当前移动速度大小。"))
	float Speed{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "速度向量", ToolTip = "当前世界空间速度向量。"))
	FVector Velocity{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "速度偏航角", ToolTip = "当前速度方向对应的偏航角。"))
	float VelocityYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "正在移动", ToolTip = "当前是否被判定为正在移动。"))
	uint8 bMoving : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "阻止朝最后输入方向旋转", ToolTip = "当前是否阻止角色朝最后一次输入方向旋转。"))
	uint8 bRotationTowardsLastInputDirectionBlocked : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "目标偏航角", ToolTip = "当前角色旋转的目标偏航角。"))
	float TargetYawAngle{0.0f};

	// Used for extra smooth actor rotation, in other cases equal to the regular target yaw angle.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "平滑目标偏航角", ToolTip = "用于额外平滑旋转的目标偏航角。"))
	float SmoothTargetYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "视角相对目标偏航角", ToolTip = "相对视角计算得到的目标偏航角。"))
	float ViewRelativeTargetYawAngle{0.0f};

	// Specifies the maximum angle by which the actor's rotation can differ from the view rotation when aiming.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "瞄准偏航角限制", ToolTip = "瞄准时角色旋转相对视角允许偏离的最大角度。"))
	float AimingYawAngleLimit{180.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "本帧应用了瞄准限制", ToolTip = "当前帧是否应用了瞄准偏航角限制。"))
	uint8 bAimingLimitAppliedThisFrame : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "重置瞄准限制", ToolTip = "下一次更新时是否需要重置瞄准限制。"))
	uint8 bResetAimingLimit : 1 {true};
};
