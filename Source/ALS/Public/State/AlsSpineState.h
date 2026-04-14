#pragma once

#include "AlsSpineState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsSpineState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "允许脊椎旋转", ToolTip = "当前是否允许脊椎执行瞄准旋转。"))
	uint8 bSpineRotationAllowed : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "脊椎权重", ToolTip = "脊椎旋转的混合权重。"))
	float SpineAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "脊椎权重缩放", ToolTip = "脊椎旋转权重的缩放系数。"))
	float SpineAmountScale{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "脊椎权重偏置", ToolTip = "脊椎旋转权重的偏置值。"))
	float SpineAmountBias{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "上一帧偏航角", ToolTip = "上一帧脊椎偏航角。"))
	float LastYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "当前偏航角", ToolTip = "当前脊椎偏航角。"))
	float CurrentYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "输出偏航角", ToolTip = "最终输出到动画的脊椎偏航角。"))
	float YawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "上一帧角色偏航角", ToolTip = "上一帧角色本体偏航角。"))
	float LastActorYawAngle{0.0f};
};
