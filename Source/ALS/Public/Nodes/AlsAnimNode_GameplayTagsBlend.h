#pragma once

#include "GameplayTagContainer.h"
#include "AnimNodes/AnimNode_BlendListBase.h"
#include "AlsAnimNode_GameplayTagsBlend.generated.h"

class UAlsAnimGraphNode_GameplayTagsBlend;

USTRUCT()
struct ALS_API FAlsAnimNode_GameplayTagsBlend : public FAnimNode_BlendListBase
{
	GENERATED_BODY()

	friend UAlsAnimGraphNode_GameplayTagsBlend;

protected:
	UPROPERTY(EditAnywhere, Category = "ALS|动画节点|设置",
		Meta = (PinShownByDefault, DisplayName = "激活标签", ToolTip = "当前用于选择子姿势的 Gameplay Tag。"))
	FGameplayTag ActiveTag;

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category = "ALS|动画节点|设置",
		Meta = (FoldProperty, DisplayName = "标签列表", ToolTip = "该节点可切换的 Gameplay Tag 列表。"))
	TArray<FGameplayTag> Tags;
#endif

protected:
	virtual int32 GetActiveChildIndex() override;

public:
	const TArray<FGameplayTag>& GetTags() const;

#if WITH_EDITOR
	void RefreshPosePins();
#endif
};
