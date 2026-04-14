#pragma once

#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Utility/AlsGameplayTags.h"
#include "AlsAnimNotifyState_EarlyBlendOut.generated.h"

UCLASS(DisplayName = "ALS 提前淡出动画通知状态")
class ALS_API UAlsAnimNotifyState_EarlyBlendOut : public UAnimNotifyState
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (ForceUnits = "s", DisplayName = "淡出时长", ToolTip = "满足条件时提前淡出的混合时长。"))
	float BlendOutDuration{0.25f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (DisplayName = "检查输入", ToolTip = "启用后，会根据输入状态决定是否提前淡出。"))
	uint8 bCheckInput : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (InlineEditConditionToggle, DisplayName = "检查移动模式", ToolTip = "启用后，会根据移动模式决定是否提前淡出。"))
	uint8 bCheckLocomotionMode : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (InlineEditConditionToggle, DisplayName = "检查旋转模式", ToolTip = "启用后，会根据旋转模式决定是否提前淡出。"))
	uint8 bCheckRotationMode : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (InlineEditConditionToggle, DisplayName = "检查姿态", ToolTip = "启用后，会根据姿态决定是否提前淡出。"))
	uint8 bCheckStance : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (EditCondition = "bCheckLocomotionMode", DisplayName = "移动模式等于", ToolTip = "需要匹配的移动模式标签。"))
	FGameplayTag LocomotionModeEquals{AlsLocomotionModeTags::InAir};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (EditCondition = "bCheckRotationMode", DisplayName = "旋转模式等于", ToolTip = "需要匹配的旋转模式标签。"))
	FGameplayTag RotationModeEquals{AlsRotationModeTags::Aiming};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (EditCondition = "bCheckStance", DisplayName = "姿态等于", ToolTip = "需要匹配的姿态标签。"))
	FGameplayTag StanceEquals{AlsStanceTags::Crouching};

public:
	UAlsAnimNotifyState_EarlyBlendOut();

	virtual FString GetNotifyName_Implementation() const override;

#if WITH_EDITOR
	virtual bool CanBePlaced(UAnimSequenceBase* Sequence) const override;
#endif

	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& NotifyPayload, float DeltaTime) override;
};
