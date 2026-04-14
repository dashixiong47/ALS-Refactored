#pragma once

#include "AlsHeadState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsHeadState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "需要初始化", ToolTip = "头部状态是否需要重新初始化。"))
	uint8 bInitializationRequired : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "正在切换观察侧", ToolTip = "当前是否正在切换左右观察方向。"))
	uint8 bSwitchingLookSides : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -90, ClampMax = 90, ForceUnits = "deg", DisplayName = "俯仰角", ToolTip = "头部当前俯仰角。"))
	float PitchAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "偏航角", ToolTip = "头部当前偏航角。"))
	float YawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ForceUnits = "deg/s", DisplayName = "偏航角速度", ToolTip = "头部偏航变化速度。"))
	float YawVelocity{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "偏航混合量", ToolTip = "头部偏航的混合权重。"))
	float YawAmount{0.5f};
};
