#pragma once

#include "AlsMovementBaseState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsMovementBaseState
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "基底组件", ToolTip = "当前角色依附的移动基底组件。"))
	TObjectPtr<UPrimitiveComponent> Primitive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "骨骼名称", ToolTip = "当前依附基底使用的骨骼名称。"))
	FName BoneName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "基底已变化", ToolTip = "当前帧移动基底是否发生变化。"))
	uint8 bBaseChanged : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "有相对位置", ToolTip = "当前是否存在相对于基底的相对位置。"))
	uint8 bHasRelativeLocation : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "有相对旋转", ToolTip = "当前是否存在相对于基底的相对旋转。"))
	uint8 bHasRelativeRotation : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "位置", ToolTip = "当前移动基底的位置。"))
	FVector Location{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "旋转四元数", ToolTip = "当前移动基底旋转的四元数表示。"))
	FQuat Rotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "增量旋转", ToolTip = "相对上一帧的基底旋转增量。"))
	FRotator DeltaRotation{ForceInit};
};
