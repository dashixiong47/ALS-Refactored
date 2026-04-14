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
	High,
	Low,
	InAir
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingParameters
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越参数",
		Meta = (DisplayName = "目标组件", ToolTip = "当前翻越所依附的目标组件。"))
	TWeakObjectPtr<UPrimitiveComponent> TargetPrimitive;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越参数",
		Meta = (DisplayName = "目标位置", ToolTip = "翻越目标位置。"))
	FVector_NetQuantize100 TargetLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越参数",
		Meta = (DisplayName = "目标旋转", ToolTip = "翻越目标旋转。"))
	FRotator TargetRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越参数",
		Meta = (ForceUnits = "cm", DisplayName = "翻越高度", ToolTip = "当前翻越动作的高度。"))
	float MantlingHeight{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越参数",
		Meta = (DisplayName = "翻越类型", ToolTip = "当前翻越动作的类型。"))
	EAlsMantlingType MantlingType{EAlsMantlingType::High};
};

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsMantlingSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (DisplayName = "翻越蒙太奇", ToolTip = "翻越动作使用的动画蒙太奇。"))
	TObjectPtr<UAnimMontage> Montage;

	// If checked, mantling will automatically calculate the start time based on how much vertical
	// distance the character needs to move to reach the object they are about to mantle.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (ClampMin = 0, DisplayName = "自动计算开始时间", ToolTip = "启用后，会根据角色需要上升的高度自动计算翻越开始时间。"))
	uint8 bAutoCalculateStartTime : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (ClampMin = 0, EditCondition = "!bAutoCalculateStartTime", DisplayName = "开始时间参考高度",
		        ToolTip = "关闭自动计算开始时间时，用于映射开始时间的参考高度区间。"))
	FVector2f StartTimeReferenceHeight{50.0f, 100.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (ClampMin = 0, EditCondition = "!bAutoCalculateStartTime", DisplayName = "开始时间",
		        ToolTip = "关闭自动计算开始时间时，不同参考高度对应的翻越开始时间。"))
	FVector2f StartTime{0.5f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (ClampMin = 0, ForceUnits = "t", DisplayName = "运动扭曲时间范围", ToolTip = "翻越时允许进行 Motion Warping 的时间区间。"))
	FFloatInterval MotionWarpingTimeRange{0.0f, 0.3f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (DisplayName = "位置扭曲混合方式", ToolTip = "Motion Warping 位置混合使用的 Alpha 混合方式。"))
	EAlphaBlendOption MotionWarpingLocationBlendOption{EAlphaBlendOption::Linear};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (EditCondition = "MotionWarpingLocationBlendOption == EAlphaBlendOption::Custom", EditConditionHides,
		        DisplayName = "位置扭曲自定义混合曲线", ToolTip = "当位置扭曲混合方式为自定义时使用的曲线。"))
	TObjectPtr<UCurveFloat> MotionWarpingLocationCustomBlendCurve;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (DisplayName = "旋转扭曲混合方式", ToolTip = "Motion Warping 旋转混合使用的 Alpha 混合方式。"))
	EAlphaBlendOption MotionWarpingRotationBlendOption{EAlphaBlendOption::HermiteCubic};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|翻越设置",
		Meta = (EditCondition = "MotionWarpingRotationBlendOption == EAlphaBlendOption::Custom", EditConditionHides,
		        DisplayName = "旋转扭曲自定义混合曲线", ToolTip = "当旋转扭曲混合方式为自定义时使用的曲线。"))
	TObjectPtr<UCurveFloat> MotionWarpingRotationCustomBlendCurve;
};

USTRUCT(BlueprintType)
struct ALS_API FAlsMantlingTraceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越检测",
		Meta = (ClampMin = 0, DisplayName = "边缘高度范围", ToolTip = "允许翻越的边缘高度范围。"))
	FVector2f LedgeHeight{50.0f, 225.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越检测",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "可达距离", ToolTip = "翻越检测允许的前向可达距离。"))
	float ReachDistance{75.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越检测",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "目标位置偏移", ToolTip = "翻越目标位置的偏移量。"))
	float TargetLocationOffset{15.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越检测",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "起始位置偏移", ToolTip = "翻越起始位置的偏移量。"))
	float StartLocationOffset{55.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越检测",
		Meta = (ClampMin = 0, DisplayName = "绘制失败检测", ToolTip = "启用后，会绘制翻越失败时的检测结果。"))
	uint8 bDrawFailedTraces : 1 {false};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsGeneralMantlingSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (DisplayName = "允许翻越", ToolTip = "是否允许角色执行翻越动作。"))
	uint8 bAllowMantling : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "检测角度阈值", ToolTip = "翻越检测时允许的最大检测角度阈值。"))
	float TraceAngleThreshold{110.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "最大可达角度", ToolTip = "允许开始翻越的最大可达角度。"))
	float MaxReachAngle{50.0f};

	// Prevents mantling on surfaces whose slope angle exceeds this value.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (ClampMin = 0, ClampMax = 90, ForceUnits = "deg", DisplayName = "坡度角阈值", ToolTip = "表面坡度角超过该值时不允许翻越。"))
	float SlopeAngleThreshold{35.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置", AdvancedDisplay,
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "坡度角余弦阈值", ToolTip = "由坡度角阈值推导出的余弦值缓存。"))
	float SlopeAngleThresholdCos{FMath::Cos(FMath::DegreesToRadians(35.0f))};

	// If a dynamic object has a speed bigger than this value, then do not start mantling.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (ForceUnits = "cm/s", DisplayName = "目标组件速度阈值", ToolTip = "动态目标速度高于该值时，不会开始翻越。"))
	float TargetPrimitiveSpeedThreshold{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (ForceUnits = "cm", DisplayName = "高翻越高度阈值", ToolTip = "高翻越与低翻越的高度分界阈值。"))
	float MantlingHighHeightThreshold{125.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (DisplayName = "地面检测设置", ToolTip = "角色在地面时使用的翻越检测设置。"))
	FAlsMantlingTraceSettings GroundedTrace;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (DisplayName = "空中检测设置", ToolTip = "角色在空中时使用的翻越检测设置。"))
	FAlsMantlingTraceSettings InAirTrace{
		.LedgeHeight = {50.0f, 150.0f},
		.ReachDistance = 70.0f
	};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (DisplayName = "翻越检测通道", ToolTip = "翻越检测主射线使用的碰撞通道。"))
	TEnumAsByte<ECollisionChannel> MantlingTraceChannel{ECC_Visibility};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (DisplayName = "翻越响应通道", ToolTip = "翻越检测需要采样的碰撞响应通道列表。"))
	TArray<TEnumAsByte<ECollisionChannel>> MantlingTraceResponseChannels;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置", AdvancedDisplay,
		Meta = (DisplayName = "翻越响应容器", ToolTip = "由翻越响应通道生成的碰撞响应缓存。"))
	FCollisionResponseContainer MantlingTraceResponses{ECR_Ignore};

	// Used when the mantling was interrupted and we need to stop the animation.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "淡出时长", ToolTip = "翻越被打断时用于停止动画的淡出时长。"))
	float BlendOutDuration{0.3f};

	// If checked, ragdolling will start if the object the character is mantling on was destroyed.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|翻越总设置",
		Meta = (DisplayName = "目标销毁时开始布娃娃", ToolTip = "启用后，翻越目标被销毁时角色会进入布娃娃。"))
	uint8 bStartRagdollingOnTargetPrimitiveDestruction : 1 {true};

public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};
