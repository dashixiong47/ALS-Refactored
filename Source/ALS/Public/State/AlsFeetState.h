#pragma once

#include "AlsFeetState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsFootState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "锁定量", ToolTip = "当前脚部锁定权重。"))
	float LockAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "大腿轴向", ToolTip = "当前脚对应大腿骨的参考轴向。"))
	FVector3f ThighAxis{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "目标位置", ToolTip = "脚部修正的目标位置。"))
	FVector TargetLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "目标旋转", ToolTip = "脚部修正的目标旋转。"))
	FQuat TargetRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "锁定位置", ToolTip = "脚部锁定时缓存的位置。"))
	FVector LockLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "锁定旋转", ToolTip = "脚部锁定时缓存的旋转。"))
	FQuat LockRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "组件相对锁定位置", ToolTip = "脚部相对组件空间的锁定位置。"))
	FVector3f LockComponentRelativeLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "组件相对锁定旋转", ToolTip = "脚部相对组件空间的锁定旋转。"))
	FQuat4f LockComponentRelativeRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "基底相对锁定位置", ToolTip = "脚部相对移动基底空间的锁定位置。"))
	FVector3f LockMovementBaseRelativeLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "基底相对锁定旋转", ToolTip = "脚部相对移动基底空间的锁定旋转。"))
	FQuat4f LockMovementBaseRelativeRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "最终位置", ToolTip = "脚部修正后最终应用的位置。"))
	FVector3f FinalLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "最终旋转", ToolTip = "脚部修正后最终应用的旋转。"))
	FQuat4f FinalRotation{ForceInit};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsFeetState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "骨盆旋转", ToolTip = "脚部修正使用的骨盆旋转。"))
	FQuat4f PelvisRotation{ForceInit};

	// Choose whether a foot is planted or about to plant when stopping using the foot planted animation
	// curve. A value less than 0.5 means the foot is planted and a value more than 0.5 means the
	// foot is still in the air. The foot planted curve also determines which foot is planted (or
	// about to plant). Positive values mean the right foot is planted, negative values mean the left.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -1, ClampMax = 1, DisplayName = "脚落地量", ToolTip = "用于判断哪只脚已落地或即将落地的曲线值。"))
	float FootPlantedAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "双脚交叉量", ToolTip = "当前双脚相互交叉的程度。"))
	float FeetCrossingAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "有效", ToolTip = "当前脚部状态是否有效。"))
	uint8 bValid : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "刚变为有效", ToolTip = "当前帧脚部状态是否刚刚变为有效。"))
	uint8 bBecameValid : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "左脚状态", ToolTip = "左脚的完整锁定与修正状态。"))
	FAlsFootState Left{
		.ThighAxis = -FVector3f::ZAxisVector
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "右脚状态", ToolTip = "右脚的完整锁定与修正状态。"))
	FAlsFootState Right{
		.ThighAxis = FVector3f::ZAxisVector
	};
};

struct ALS_API FAlsFootUpdateContext
{
	FTransform ComponentTransform;

	FTransform ComponentTransformInverse;

	FAlsFootState* FootState{nullptr};

	float IkAmount{0.0f};

	float LockAmount{0.0f};

	float DeltaTime{0.0f};
};
