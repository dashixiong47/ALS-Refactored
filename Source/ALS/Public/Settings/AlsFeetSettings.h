#pragma once

#include "AlsFeetSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsFeetSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚部设置",
		Meta = (DisplayName = "禁用脚锁", ToolTip = "启用后，会禁用脚锁相关动画修正。"))
	uint8 bDisableFootLock : 1 {false};

	// Specifies the maximum angle by which the foot lock location can differ from the thigh
	// bone axis. Used to prevent legs from twisting into a spiral when the actor rotates quickly.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚部设置",
		Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg", DisplayName = "脚锁角度限制",
		        ToolTip = "脚锁位置相对大腿骨轴允许偏离的最大角度，用于避免快速转向时腿部扭曲。"))
	float FootLockAngleLimit{90.0f};
};
