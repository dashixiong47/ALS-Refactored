#pragma once

#include "Engine/EngineTypes.h"
#include "AlsInAirSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsInAirSettings
{
	GENERATED_BODY()

public:
	// Vertical velocity to lean amount curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|空中设置",
		Meta = (DisplayName = "倾斜量曲线", ToolTip = "垂直速度到倾斜量的映射曲线。"))
	TObjectPtr<UCurveFloat> LeanAmountCurve;

	// Ground prediction sweep hit time to ground prediction amount curve.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|空中设置",
		Meta = (DisplayName = "地面预测量曲线", ToolTip = "地面预测检测命中时间到地面预测量的映射曲线。"))
	TObjectPtr<UCurveFloat> GroundPredictionAmountCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|空中设置",
		Meta = (DisplayName = "地面预测扫描通道", ToolTip = "地面预测扫描使用的碰撞通道。"))
	TEnumAsByte<ECollisionChannel> GroundPredictionSweepChannel{ECC_Visibility};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|空中设置",
		Meta = (DisplayName = "地面预测响应通道", ToolTip = "地面预测需要采样的碰撞响应通道列表。"))
	TArray<TEnumAsByte<ECollisionChannel>> GroundPredictionResponseChannels;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS|空中设置", AdvancedDisplay,
		Meta = (DisplayName = "地面预测响应容器", ToolTip = "由地面预测响应通道生成的碰撞响应缓存。"))
	FCollisionResponseContainer GroundPredictionSweepResponses{ECR_Ignore};

public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};
