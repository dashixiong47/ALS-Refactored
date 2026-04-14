#pragma once

#include "Units/RigUnit.h"
#include "AlsRigUnit_FootOffsetTrace.generated.h"

USTRUCT(DisplayName = "脚部偏移检测", Meta = (Category = "ALS|控制绑定", NodeColor = "0.2 0.4 1.0"))
struct ALS_API FAlsRigUnit_FootOffsetTrace : public FRigUnit
{
	GENERATED_BODY()

public:
	UPROPERTY(Transient, Meta = (Input, DisplayName = "脚目标位置", ToolTip = "用于发起地面检测的脚部目标位置。"))
	FVector FootTargetLocation{ForceInit};

	UPROPERTY(Meta = (Input, DisplayName = "检测通道", ToolTip = "脚部地面检测使用的碰撞通道。"))
	TEnumAsByte<ECollisionChannel> TraceChannel{ECC_Visibility};

	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm", DisplayName = "向上检测距离",
		ToolTip = "从脚目标位置向上进行检测的距离。"))
	float TraceDistanceUpward{50.0f};

	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm", DisplayName = "向下检测距离",
		ToolTip = "从脚目标位置向下进行检测的距离。"))
	float TraceDistanceDownward{80.0f};

	UPROPERTY(Meta = (Input, ClampMin = 0, ClampMax = 90, ForceUnits = "deg", DisplayName = "可行走地面角度",
		ToolTip = "判定地面可行走时允许的最大坡度角。"))
	float WalkableFloorAngle{45.0f};

	UPROPERTY(Meta = (Input, ClampMin = 0, ForceUnits = "cm", DisplayName = "脚部高度",
		ToolTip = "脚底到脚部参考点的垂直高度。"))
	float FootHeight{13.5f};

	UPROPERTY(Meta = (Input, DisplayName = "启用", ToolTip = "是否执行脚部偏移地面检测。"))
	bool bEnabled{true};

	UPROPERTY(Meta = (Input, DetailsOnly, DisplayName = "绘制调试", ToolTip = "是否绘制脚部检测的调试信息。"))
	bool bDrawDebug{false};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "偏移 Z", ToolTip = "检测得到的脚部垂直偏移量。"))
	float OffsetLocationZ{0.0f};

	UPROPERTY(Transient, Meta = (Output, DisplayName = "偏移法线", ToolTip = "检测命中表面的法线方向。"))
	FVector OffsetNormal{ForceInit};

public:
	RIGVM_METHOD()
	virtual void Execute() override;
};
