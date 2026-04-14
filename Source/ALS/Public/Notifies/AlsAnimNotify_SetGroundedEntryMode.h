#pragma once

#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AlsAnimNotify_SetGroundedEntryMode.generated.h"

UCLASS(DisplayName = "ALS 设置地面进入模式动画通知")
class ALS_API UAlsAnimNotify_SetGroundedEntryMode : public UAnimNotify
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (DisplayName = "地面进入模式", ToolTip = "通知触发时写入角色的地面进入模式标签。"))
	FGameplayTag GroundedEntryMode;

public:
	UAlsAnimNotify_SetGroundedEntryMode();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence,
	                    const FAnimNotifyEventReference& NotifyEventReference) override;
};
