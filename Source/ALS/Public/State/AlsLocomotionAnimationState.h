#pragma once

#include "AlsLocomotionAnimationState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsLocomotionAnimationState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "有输入", ToolTip = "当前是否存在有效的移动输入。"))
	uint8 bHasInput : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "输入偏航角", ToolTip = "当前输入方向对应的偏航角。"))
	float InputYawAngle{0.0f};

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
		Meta = (DisplayName = "加速度", ToolTip = "当前世界空间加速度向量。"))
	FVector Acceleration{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "cm/s^2", DisplayName = "最大加速度", ToolTip = "当前允许的最大加速度。"))
	float MaxAcceleration{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, DisplayName = "最大制动减速度", ToolTip = "当前允许的最大制动减速度。"))
	float MaxBrakingDeceleration{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "可行走地面角余弦", ToolTip = "当前可行走地面角的余弦值。"))
	float WalkableFloorAngleCos{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "正在移动", ToolTip = "当前是否被判定为正在移动。"))
	uint8 bMoving : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "平滑移动中", ToolTip = "当前是否被判定为平滑移动状态。"))
	uint8 bMovingSmooth : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "目标偏航角", ToolTip = "当前角色旋转的目标偏航角。"))
	float TargetYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "位置", ToolTip = "当前角色位置。"))
	FVector Location{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "旋转", ToolTip = "当前角色旋转。"))
	FRotator Rotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "旋转四元数", ToolTip = "当前角色旋转的四元数表示。"))
	FQuat RotationQuaternion{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ForceUnits = "deg/s", DisplayName = "偏航角速度", ToolTip = "当前角色偏航变化速度。"))
	float YawVelocity{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ForceUnits = "x", DisplayName = "缩放", ToolTip = "当前角色缩放值。"))
	float Scale{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "胶囊半径", ToolTip = "当前角色胶囊体半径。"))
	float CapsuleRadius{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "胶囊半高", ToolTip = "当前角色胶囊体半高。"))
	float CapsuleHalfHeight{0.0f};
};
