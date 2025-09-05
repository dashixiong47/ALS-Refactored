#pragma once

#include "AlsRotateInPlaceSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsRotateInPlaceSettings
{
	GENERATED_BODY()

	// 视角偏航角阈值（度）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"), DisplayName="视角偏航角阈值")
	float ViewYawAngleThreshold{50.0f};

	// 参考视角偏航速度（最小值, 最大值）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="参考视角偏航速度")
	FVector2f ReferenceViewYawSpeed{180.0f, 460.0f};

	// 播放速率范围（最小值, 最大值）
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="播放速率范围")
	FVector2f PlayRate{1.15f, 3.0f};

};
