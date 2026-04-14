#pragma once

#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AlsAnimNotifyState_SetLocomotionAction.generated.h"

UCLASS(DisplayName = "ALS 设置移动动作动画通知状态")
class ALS_API UAlsAnimNotifyState_SetLocomotionAction : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (DisplayName = "移动动作", ToolTip = "通知持续期间要设置到角色上的移动动作标签。"))
	FGameplayTag LocomotionAction;

public:
	UAlsAnimNotifyState_SetLocomotionAction();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence,
	                         float Duration, const FAnimNotifyEventReference& NotifyEventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence,
	                       const FAnimNotifyEventReference& NotifyEventReference) override;
};
