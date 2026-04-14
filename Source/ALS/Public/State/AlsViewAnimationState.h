#pragma once

#include "AlsViewAnimationState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsViewAnimationState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "旋转", ToolTip = "当前动画使用的视角旋转。"))
	FRotator Rotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "偏航角", ToolTip = "当前视角偏航角。"))
	float YawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "deg/s", DisplayName = "偏航速度", ToolTip = "当前视角偏航速度。"))
	float YawSpeed{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -90, ClampMax = 90, ForceUnits = "deg", DisplayName = "俯仰角", ToolTip = "当前视角俯仰角。"))
	float PitchAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "俯仰权重", ToolTip = "当前俯仰混合权重。"))
	float PitchAmount{0.5f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "头部混合量", ToolTip = "视角对头部旋转的混合权重。"))
	float HeadBlendAmount{1.0f};
};
