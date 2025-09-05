#pragma once

#include "AlsTurnInPlaceSettings.generated.h"

class UAnimSequenceBase;

UCLASS(BlueprintType, EditInlineNew)
class ALS_API UAlsTurnInPlaceSettings : public UObject
{
	GENERATED_BODY()

public:
	// 动画序列
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="动画序列")
	TObjectPtr<UAnimSequenceBase> Sequence;

	// 播放速率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, ForceUnits = "x"), DisplayName="播放速率")
	float PlayRate{1.2f};

	// 是否根据动画旋转角度缩放播放速率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="根据动画旋转角度缩放播放速率")
	uint8 bScalePlayRateByAnimatedTurnAngle : 1 {true};

	// 动画旋转角度（度）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0.0001, ClampMax = 180, ForceUnits = "deg"), DisplayName="动画旋转角度")
	float AnimatedTurnAngle{0.0f};

};
USTRUCT(BlueprintType)
struct ALS_API FAlsGeneralTurnInPlaceSettings
{
	GENERATED_BODY()

	// 视角偏航角阈值，超过该角度将触发原地转向
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "视角偏航角阈值", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"))
	float ViewYawAngleThreshold{45.0f};

	// 视角偏航速度阈值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "视角偏航速度阈值", Meta = (ClampMin = 0, ForceUnits = "deg/s"))
	float ViewYawSpeedThreshold{50.0f};

	// 视角偏航角到触发延迟的映射
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "视角偏航角到触发延迟", Meta = (ClampMin = 0))
	FVector2f ViewYawAngleToActivationDelay{0.0f, 0.75f};

	// 转向180°触发阈值
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "转向180°阈值", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"))
	float Turn180AngleThreshold{130.0f};

	// 混合持续时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName = "混合持续时间", Meta = (ClampMin = 0, ForceUnits = "s"))
	float BlendDuration{0.2f};

	// 站立状态下向左转90°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "站立转向90°左")
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn90Left;

	// 站立状态下向右转90°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "站立转向90°右")
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn90Right;

	// 站立状态下向左转180°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "站立转向180°左")
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn180Left;

	// 站立状态下向右转180°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "站立转向180°右")
	TObjectPtr<UAlsTurnInPlaceSettings> StandingTurn180Right;

	// 下蹲状态下向左转90°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "下蹲转向90°左")
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn90Left;

	// 下蹲状态下向右转90°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "下蹲转向90°右")
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn90Right;

	// 下蹲状态下向左转180°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "下蹲转向180°左")
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn180Left;

	// 下蹲状态下向右转180°设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Instanced, DisplayName = "下蹲转向180°右")
	TObjectPtr<UAlsTurnInPlaceSettings> CrouchingTurn180Right;
};

