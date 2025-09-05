#pragma once

#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "Engine/NetSerialization.h"
#include "AlsMantlingSettings.generated.h"

class UAnimMontage;
class UCurveFloat;

UENUM(BlueprintType)
enum class EAlsMantlingType : uint8
{
	High,   // 高翻越
	Low,    // 低翻越
	InAir   // 空中翻越
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingParameters
{
	GENERATED_BODY()

	// 目标组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="目标组件"))
	TWeakObjectPtr<UPrimitiveComponent> TargetPrimitive;

	// 相对目标位置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="目标相对位置"))
	FVector_NetQuantize100 TargetRelativeLocation{ForceInit};

	// 相对目标旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="目标相对旋转"))
	FRotator TargetRelativeRotation{ForceInit};

	// 翻越高度（cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm", DisplayName="翻越高度"))
	float MantlingHeight{0.0f};

	// 翻越类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="翻越类型"))
	EAlsMantlingType MantlingType{EAlsMantlingType::High};
};

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsMantlingSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	// 使用的动画蒙太奇
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (DisplayName="蒙太奇"))
	TObjectPtr<UAnimMontage> Montage;

	// 是否自动计算开始时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, DisplayName="自动计算开始时间"))
	uint8 bAutoCalculateStartTime : 1 {false};

	// 用于参考的高度范围
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, EditCondition = "!bAutoCalculateStartTime", DisplayName="开始时间参考高度"))
	FVector2f StartTimeReferenceHeight{50.0f, 100.0f};

	// 起始时间范围
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, EditCondition = "!bAutoCalculateStartTime", DisplayName="开始时间"))
	FVector2f StartTime{0.5f, 0.0f};

	// 可选：水平校正曲线
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (DisplayName="水平校正曲线"))
	TObjectPtr<UCurveFloat> HorizontalCorrectionCurve;

	// 可选：垂直校正曲线
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", meta = (DisplayName="垂直校正曲线"))
	TObjectPtr<UCurveFloat> VerticalCorrectionCurve;
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingTraceSettings
{
	GENERATED_BODY()

	// 岩沿高度范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, DisplayName="岩沿高度"))
	FVector2f LedgeHeight{50.0f, 225.0f};

	// 可触及距离（cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName="可触及距离"))
	float ReachDistance{75.0f};

	// 目标位置偏移（cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName="目标位置偏移"))
	float TargetLocationOffset{15.0f};

	// 起始位置偏移（cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName="起始位置偏移"))
	float StartLocationOffset{55.0f};

	// 是否绘制失败检测线
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, DisplayName="绘制失败检测线"))
	uint8 bDrawFailedTraces : 1 {false};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsGeneralMantlingSettings
{
	GENERATED_BODY()

public:
	// 是否允许翻越
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="允许翻越"))
	uint8 bAllowMantling : 1 {true};

	// 检测角度阈值（度）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName="检测角度阈值"))
	float TraceAngleThreshold{110.0f};

	// 最大可触及角度（度）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName="最大可触及角度"))
	float MaxReachAngle{50.0f};

	// 防止斜面翻越的角度阈值（度）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 90, ForceUnits = "deg", DisplayName="斜面角度阈值"))
	float SlopeAngleThreshold{35.0f};

	// 斜面角度余弦值（高级显示）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, Meta = (ClampMin = 0, ClampMax = 1, DisplayName="斜面角度余弦"))
	float SlopeAngleThresholdCos{FMath::Cos(FMath::DegreesToRadians(35.0f))};

	// 动态对象速度阈值（cm/s）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm/s", DisplayName="目标组件速度阈值"))
	float TargetPrimitiveSpeedThreshold{10.0f};

	// 高翻越高度阈值（cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm", DisplayName="高翻越高度阈值"))
	float MantlingHighHeightThreshold{125.0f};

	// 地面翻越检测设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="地面翻越检测"))
	FAlsMantlingTraceSettings GroundedTrace;

	// 空中翻越检测设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="空中翻越检测"))
	FAlsMantlingTraceSettings InAirTrace{{50.0f, 150.0f}, 70.0f};

	// 翻越检测通道
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="翻越检测通道"))
	TEnumAsByte<ECollisionChannel> MantlingTraceChannel{ECC_Visibility};

	// 翻越检测响应通道
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="翻越检测响应通道"))
	TArray<TEnumAsByte<ECollisionChannel>> MantlingTraceResponseChannels;

	// 翻越检测响应容器（高级显示）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, meta = (DisplayName="翻越检测响应容器"))
	FCollisionResponseContainer MantlingTraceResponses{ECR_Ignore};

	// 翻越被中断时的混合消失时间（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s", DisplayName="混合消失时间"))
	float BlendOutDuration{0.3f};

	// 如果翻越目标被销毁，是否开始布娃娃
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", meta = (DisplayName="目标销毁时启动布娃娃"))
	uint8 bStartRagdollingOnTargetPrimitiveDestruction : 1 {true};


public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};
