#pragma once

#include "AlsPoseState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsPoseState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "地面权重", ToolTip = "地面姿势的混合权重。"))
	float GroundedAmount{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "空中权重", ToolTip = "空中姿势的混合权重。"))
	float InAirAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "站立权重", ToolTip = "站立姿势的混合权重。"))
	float StandingAmount{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "蹲伏权重", ToolTip = "蹲伏姿势的混合权重。"))
	float CrouchingAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "移动权重", ToolTip = "移动姿势的混合权重。"))
	float MovingAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 3, DisplayName = "步态权重", ToolTip = "当前步态的综合混合权重。"))
	float GaitAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "步行权重", ToolTip = "步行步态的混合权重。"))
	float GaitWalkingAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "跑步权重", ToolTip = "跑步步态的混合权重。"))
	float GaitRunningAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "冲刺权重", ToolTip = "冲刺步态的混合权重。"))
	float GaitSprintingAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 3, DisplayName = "未加权步态权重", ToolTip = "未经过姿态加权的步态综合权重。"))
	float UnweightedGaitAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "未加权步行权重", ToolTip = "未经过姿态加权的步行权重。"))
	float UnweightedGaitWalkingAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "未加权跑步权重", ToolTip = "未经过姿态加权的跑步权重。"))
	float UnweightedGaitRunningAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "未加权冲刺权重", ToolTip = "未经过姿态加权的冲刺权重。"))
	float UnweightedGaitSprintingAmount{0.0f};
};
