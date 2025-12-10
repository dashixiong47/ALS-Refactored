#pragma once

#include "AlphaBlend.h"
#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "Engine/NetSerialization.h"
#include "AlsMantlingSettings.generated.h"

class UAnimMontage;
class UCurveFloat;

UENUM(BlueprintType)
enum class EAlsMantlingType : uint8
{
	High UMETA(DisplayName = "高"),
	Low UMETA(DisplayName = "低"),
	InAir UMETA(DisplayName = "空中")
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingParameters
{
	GENERATED_BODY()

	// 目标的原始组件
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "目标原始组件")
	TWeakObjectPtr<UPrimitiveComponent> TargetPrimitive;

	// 目标位置（网络量化）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "目标位置")
	FVector_NetQuantize100 TargetLocation{ForceInit};

	// 目标旋转
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "目标旋转")
	FRotator TargetRotation{ForceInit};

	// 攀爬高度（单位：cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm"), DisplayName = "攀爬高度")
	float MantlingHeight{0.0f};

	// 攀爬类型（高/低/空中）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "攀爬类型")
	EAlsMantlingType MantlingType{EAlsMantlingType::High};
};

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsMantlingSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	// 用于攀爬的动画蒙太奇
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName = "动画蒙太奇")
	TObjectPtr<UAnimMontage> Montage;

	// 如果勾选，攀爬会基于垂直距离自动计算动画起始时间
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0), DisplayName = "自动计算起始时间")
	uint8 bAutoCalculateStartTime : 1 {false};

	// 起始时间参考高度（当未自动计算时使用）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, EditCondition = "!bAutoCalculateStartTime"), DisplayName = "起始时间参考高度")
	FVector2f StartTimeReferenceHeight{50.0f, 100.0f};

	// 起始时间范围（当未自动计算时使用）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, EditCondition = "!bAutoCalculateStartTime"), DisplayName = "起始时间")
	FVector2f StartTime{0.5f, 0.0f};

	// 运动扭曲时间范围（单位：s）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, ForceUnits = "t"), DisplayName = "运动扭曲时间范围")
	FFloatInterval MotionWarpingTimeRange{0.0f, 0.3f};

	// 位置混合选项
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName = "位置混合选项")
	EAlphaBlendOption MotionWarpingLocationBlendOption{EAlphaBlendOption::Linear};

	// 自定义位置混合曲线（仅在混合选项为 Custom 时显示）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings",
		Meta = (EditCondition = "MotionWarpingLocationBlendOption == EAlphaBlendOption::Custom", EditConditionHides), DisplayName = "位置自定义混合曲线")
	TObjectPtr<UCurveFloat> MotionWarpingLocationCustomBlendCurve;

	// 旋转混合选项
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName = "旋转混合选项")
	EAlphaBlendOption MotionWarpingRotationBlendOption{EAlphaBlendOption::HermiteCubic};

	// 自定义旋转混合曲线（仅在混合选项为 Custom 时显示）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings",
		Meta = (EditCondition = "MotionWarpingRotationBlendOption == EAlphaBlendOption::Custom", EditConditionHides), DisplayName = "旋转自定义混合曲线")
	TObjectPtr<UCurveFloat> MotionWarpingRotationCustomBlendCurve;
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingTraceSettings
{
	GENERATED_BODY()

	// 台阶高度范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName = "台阶高度范围")
	FVector2f LedgeHeight{50.0f, 225.0f};

	// 可达距离（单位：cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm"), DisplayName = "可达距离")
	float ReachDistance{75.0f};

	// 目标位置偏移（单位：cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm"), DisplayName = "目标位置偏移")
	float TargetLocationOffset{15.0f};

	// 起始位置偏移（单位：cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "cm"), DisplayName = "起始位置偏移")
	float StartLocationOffset{55.0f};

	// 是否绘制失败的射线（调试用）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName = "绘制失败射线")
	uint8 bDrawFailedTraces : 1 {false};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsGeneralMantlingSettings
{
	GENERATED_BODY()

public:
	// 是否允许攀爬
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "允许攀爬")
	uint8 bAllowMantling : 1 {true};

	// 射线角度阈值（单位：deg）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"), DisplayName = "射线角度阈值")
	float TraceAngleThreshold{110.0f};

	// 最大可达角度（单位：deg）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"), DisplayName = "最大可达角度")
	float MaxReachAngle{50.0f};

	// 防止在坡度超过此值的表面上攀爬（单位：deg）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 90, ForceUnits = "deg"), DisplayName = "坡度角阈值")
	float SlopeAngleThreshold{35.0f};

	// 坡度角阈值的余弦值（只读，便于蓝图显示）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, Meta = (ClampMin = 0, ClampMax = 1), DisplayName = "坡度角阈值余弦")
	float SlopeAngleThresholdCos{FMath::Cos(FMath::DegreesToRadians(35.0f))};

	// 如果动态对象速度大于此值，则不开始攀爬（单位：cm/s）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm/s"), DisplayName = "目标物体速度阈值")
	float TargetPrimitiveSpeedThreshold{10.0f};

	// 高攀爬高度阈值（单位：cm）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ForceUnits = "cm"), DisplayName = "高攀爬高度阈值")
	float MantlingHighHeightThreshold{125.0f};

	// 地面追踪设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "地面追踪")
	FAlsMantlingTraceSettings GroundedTrace;

	// 空中追踪设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "空中追踪")
	FAlsMantlingTraceSettings InAirTrace{
		.LedgeHeight = {50.0f, 150.0f},
		.ReachDistance = 70.0f
	};

	// 攀爬追踪通道
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "攀爬追踪通道")
	TEnumAsByte<ECollisionChannel> MantlingTraceChannel{ECC_Visibility};

	// 攀爬追踪响应通道数组
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "攀爬追踪响应通道")
	TArray<TEnumAsByte<ECollisionChannel>> MantlingTraceResponseChannels;

	// 攀爬追踪响应（高级显示）
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, DisplayName = "攀爬追踪响应")
	FCollisionResponseContainer MantlingTraceResponses{ECR_Ignore};

	// 当攀爬被中断需要停止动画时使用的混出时长（单位：s）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName = "混出时长")
	float BlendOutDuration{0.3f};

	// 如果勾选，当目标物体被销毁时会进入布娃娃状态
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "目标销毁时触发布娃娃")
	uint8 bStartRagdollingOnTargetPrimitiveDestruction : 1 {true};

public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};