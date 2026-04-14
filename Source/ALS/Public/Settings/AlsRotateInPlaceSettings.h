#pragma once

#include "AlsRotateInPlaceSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsRotateInPlaceSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|原地旋转设置",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "视角偏航角阈值", ToolTip = "视角偏航超过该阈值时，会激活原地旋转。"))
	float ViewYawAngleThreshold{50.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|原地旋转设置",
		Meta = (ClampMin = 0, DisplayName = "参考视角偏航速度", ToolTip = "根据视角偏航速度映射原地旋转播放速率时使用的参考区间。"))
	FVector2f ReferenceViewYawSpeed{180.0f, 460.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|原地旋转设置",
		Meta = (ClampMin = 0, DisplayName = "播放速率范围", ToolTip = "原地旋转动画的播放速率范围。"))
	FVector2f PlayRate{1.15f, 3.0f};
};
