#pragma once

#include "Engine/EngineTypes.h"
#include "AlsInAirSettings.generated.h"

class UCurveFloat;

USTRUCT(BlueprintType)
struct ALS_API FAlsInAirSettings
{
	GENERATED_BODY()

public:
	// 垂直速度 → 倾斜量 曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="倾斜量曲线")
	TObjectPtr<UCurveFloat> LeanAmountCurve;

	// 地面预测扫描命中时间 → 地面预测量 曲线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="地面预测量曲线")
	TObjectPtr<UCurveFloat> GroundPredictionAmountCurve;

	// 地面预测扫描通道
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="地面预测扫描通道")
	TEnumAsByte<ECollisionChannel> GroundPredictionSweepChannel{ECC_Visibility};

	// 地面预测响应通道数组
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="地面预测响应通道")
	TArray<TEnumAsByte<ECollisionChannel>> GroundPredictionResponseChannels;

	// 地面预测扫描响应（高级显示）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, DisplayName="地面预测扫描响应")
	FCollisionResponseContainer GroundPredictionSweepResponses{ECR_Ignore};


public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};
