#pragma once

#include "State/AlsMovementDirection.h"
#include "AlsGroundedState.generated.h"

UENUM(BlueprintType)
enum class EAlsHipsDirection : uint8
{
	Forward,
	Backward,
	LeftForward,
	LeftBackward,
	RightForward,
	RightBackward,
};

USTRUCT(BlueprintType)
struct ALS_API FAlsVelocityBlendState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "需要初始化", ToolTip = "当前速度混合状态是否需要重新初始化。"))
	uint8 bInitializationRequired : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "前向权重", ToolTip = "前向速度混合权重。"))
	float ForwardAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "后向权重", ToolTip = "后向速度混合权重。"))
	float BackwardAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "左向权重", ToolTip = "左向速度混合权重。"))
	float LeftAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "右向权重", ToolTip = "右向速度混合权重。"))
	float RightAmount{0.0f};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsRotationYawOffsetsState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "前向角度", ToolTip = "前向移动使用的偏航角偏移。"))
	float ForwardAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "后向角度", ToolTip = "后向移动使用的偏航角偏移。"))
	float BackwardAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "左向角度", ToolTip = "左向移动使用的偏航角偏移。"))
	float LeftAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "右向角度", ToolTip = "右向移动使用的偏航角偏移。"))
	float RightAngle{0.0f};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsGroundedState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -1, ClampMax = 1, DisplayName = "髋部方向锁定量", ToolTip = "髋部方向锁定的混合权重。"))
	float HipsDirectionLockAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "髋部方向", ToolTip = "当前髋部朝向分类。"))
	EAlsHipsDirection HipsDirection{EAlsHipsDirection::Forward};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "速度混合", ToolTip = "当前地面移动使用的速度混合状态。"))
	FAlsVelocityBlendState VelocityBlend;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "移动方向缓存", ToolTip = "当前移动方向的缓存结果。"))
	FAlsMovementDirectionCache MovementDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "偏航偏移", ToolTip = "当前地面移动使用的偏航偏移状态。"))
	FAlsRotationYawOffsetsState RotationYawOffsets;
};
