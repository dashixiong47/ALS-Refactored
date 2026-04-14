#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "AlsTopDownInputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS(BlueprintType, Meta = (DisplayName = "ALS 俯视角输入配置", ToolTip = "配置 ALS 俯视角角色使用的输入映射上下文与常用输入动作。"))
class ALSEXTRAS_API UAlsTopDownInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "输入映射上下文", ToolTip = "角色被本地玩家控制时自动添加的 Enhanced Input 映射上下文。", DisplayThumbnail = false))
	TObjectPtr<UInputMappingContext> InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "移动输入动作", ToolTip = "二维移动输入动作，默认绑定到俯视角平面移动。", DisplayThumbnail = false))
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "缩放输入动作", ToolTip = "摄像机缩放输入动作，建议使用鼠标滚轮或手柄扳机。", DisplayThumbnail = false))
	TObjectPtr<UInputAction> ZoomAction;
};
