#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AlsAnimNotifyState_SetRootMotionScale.generated.h"

UCLASS(DisplayName = "ALS 设置根运动缩放动画通知状态")
class ALS_API UAlsAnimNotifyState_SetRootMotionScale : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "位移缩放", ToolTip = "通知持续期间根运动位移使用的缩放系数。"))
	float TranslationScale{1.0f};

public:
	UAlsAnimNotifyState_SetRootMotionScale();

	virtual FString GetNotifyName_Implementation() const override;

	virtual void NotifyBegin(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence,
	                         float Duration, const FAnimNotifyEventReference& NotifyEventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence,
	                       const FAnimNotifyEventReference& NotifyEventReference) override;
};
