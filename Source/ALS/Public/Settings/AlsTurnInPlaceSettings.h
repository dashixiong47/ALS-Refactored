#pragma once

#include "AlsTurnInPlaceSettings.generated.h"

class UAnimSequenceBase;

UCLASS(BlueprintType, EditInlineNew)
class ALS_API UAlsTurnInPlaceSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|转身设置",
		Meta = (DisplayName = "动画序列", ToolTip = "本组转身设置使用的动画序列。"))
	TObjectPtr<UAnimSequenceBase> Sequence;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|转身设置",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "播放速率", ToolTip = "该转身序列的基础播放速率。"))
	float PlayRate{1.2f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|转身设置",
		Meta = (DisplayName = "按动画转角缩放播放速率", ToolTip = "启用后，会根据动画实际转角自动缩放播放速率。"))
	uint8 bScalePlayRateByAnimatedTurnAngle : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|转身设置",
		Meta = (ClampMin = 0.0001, ClampMax = 180, ForceUnits = "deg", DisplayName = "动画转角", ToolTip = "该转身序列实际包含的转角大小。"))
	float AnimatedTurnAngle{0.0f};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsGeneralTurnInPlaceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "视角偏航阈值", ToolTip = "视角偏航超过该阈值时允许触发转身。"))
	float ViewYawAngleThreshold{45.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置",
		Meta = (ClampMin = 0, ForceUnits = "deg/s", DisplayName = "视角偏航速度阈值", ToolTip = "视角偏航速度超过该阈值时会抑制部分转身触发。"))
	float ViewYawSpeedThreshold{50.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置",
		Meta = (ClampMin = 0, DisplayName = "视角偏航到激活延迟", ToolTip = "不同偏航角对应的转身激活延迟区间。"))
	FVector2f ViewYawAngleToActivationDelay{0.0f, 0.75f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置",
		DisplayName = "转身 180 角度阈值",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", ToolTip = "偏航角超过该值时，会优先选择 180 度转身动作。"))
	float Turn180AngleThreshold{130.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "混合时长", ToolTip = "转身动画的混合时长。"))
	float BlendDuration{0.2f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "站立左转 90",
		Meta = (ToolTip = "站立状态下左转 90 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn90Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "站立右转 90",
		Meta = (ToolTip = "站立状态下右转 90 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn90Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "站立左转 180",
		Meta = (ToolTip = "站立状态下左转 180 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn180Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "站立右转 180",
		Meta = (ToolTip = "站立状态下右转 180 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn180Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "蹲伏左转 90",
		Meta = (ToolTip = "蹲伏状态下左转 90 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn90Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "蹲伏右转 90",
		Meta = (ToolTip = "蹲伏状态下右转 90 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn90Right;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "蹲伏左转 180",
		Meta = (ToolTip = "蹲伏状态下左转 180 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn180Left;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|总转身设置", Instanced, DisplayName = "蹲伏右转 180",
		Meta = (ToolTip = "蹲伏状态下右转 180 度使用的转身设置。"))
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn180Right;
};
