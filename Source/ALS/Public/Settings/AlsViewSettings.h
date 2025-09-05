#pragma once

#include "AlsViewSettings.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsViewSettings
{
	GENERATED_BODY()

	// 是否启用网络平滑
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS", meta = (DisplayName="启用网络平滑"))
	uint8 bEnableNetworkSmoothing : 1 {true};

	// 是否启用监听服务器的网络平滑
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS", meta = (DisplayName="启用监听服务器网络平滑"))
	uint8 bEnableListenServerNetworkSmoothing : 1 {true};
};

