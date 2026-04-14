#pragma once

#include "AlsViewSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsViewSettings
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|视角设置",
		Meta = (DisplayName = "启用网络平滑", ToolTip = "是否对远端视角旋转启用网络平滑。"))
	uint8 bEnableNetworkSmoothing : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|视角设置",
		Meta = (DisplayName = "启用监听服务器网络平滑", ToolTip = "是否在监听服务器模式下也对视角旋转启用网络平滑。"))
	uint8 bEnableListenServerNetworkSmoothing : 1 {true};
};
