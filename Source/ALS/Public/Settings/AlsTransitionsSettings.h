#pragma once

#include "AlsTransitionsSettings.generated.h"

class UAnimSequenceBase;

USTRUCT(BlueprintType)
struct ALS_API FAlsTransitionsSettings
{
	GENERATED_BODY()

	// 快速停止混合进入持续时间（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName="快速停止混合进入时间")
	float QuickStopBlendInDuration{0.1f};

	// 快速停止混合退出持续时间（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName="快速停止混合退出时间")
	float QuickStopBlendOutDuration{0.2f};

	// 快速停止播放速率范围
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="快速停止播放速率")
	FVector2f QuickStopPlayRate{1.75f, 3.0f};

	// 快速停止动画开始时间（秒）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ForceUnits = "s"), DisplayName="快速停止开始时间")
	float QuickStopStartTime{0.3f};

	// 站立向左动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="站立向左动画序列")
	TObjectPtr<UAnimSequenceBase> StandingLeftSequence;

	// 站立向右动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="站立向右动画序列")
	TObjectPtr<UAnimSequenceBase> StandingRightSequence;

	// 蹲下向左动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="蹲下向左动画序列")
	TObjectPtr<UAnimSequenceBase> CrouchingLeftSequence;

	// 蹲下向右动画序列
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="蹲下向右动画序列")
	TObjectPtr<UAnimSequenceBase> CrouchingRightSequence;

};
