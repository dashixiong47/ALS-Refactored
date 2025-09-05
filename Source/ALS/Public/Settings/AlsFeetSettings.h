#pragma once

#include "AlsFeetSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsFeetSettings
{
	GENERATED_BODY()

	// 是否禁用脚部锁定
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="禁用脚部锁定")
	uint8 bDisableFootLock : 1 {false};

	// 脚部锁定位置与大腿骨轴线允许的最大角度（度数）
	// 用于防止角色快速旋转时腿部过度扭曲成螺旋状
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0, ClampMax = 180, ForceUnits = "deg"), DisplayName="脚部锁定角度限制")
	float FootLockAngleLimit{90.0f};

};
