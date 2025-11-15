#pragma once

#include "AnimationModifier.h"
#include "Utility/AlsConstants.h"
#include "AlsAnimationModifier_CreateLayeringCurves.generated.h"

UCLASS(DisplayName = "Als Create Layering Curves Animation Modifier")
class ALSEDITOR_API UAlsAnimationModifier_CreateLayeringCurves : public UAnimationModifier
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="覆盖已有曲线")
	uint8 bOverrideExistingCurves : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="每帧添加关键点")
	uint8 bAddKeyOnEachFrame : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="曲线名称")
	TMap<FName, float> CurveNames
	{
		{UAlsConstants::ToLeftHandIKCurveName(), 1.0f},
		{UAlsConstants::ToRightHandIKCurveName(), 1.0f},
		{UAlsConstants::LayerHeadCurveName(), 1.0f},
		{UAlsConstants::LayerHeadAdditiveCurveName(), 0.0f},
		{UAlsConstants::LayerArmLeftCurveName(), 0.0f},
		{UAlsConstants::LayerArmLeftAdditiveCurveName(), 0.0f},
		{UAlsConstants::LayerArmLeftLocalSpaceCurveName(), 0.0f},
		{UAlsConstants::LayerArmRightCurveName(), 0.0f},
		{UAlsConstants::LayerArmRightAdditiveCurveName(), 0.0f},
		{UAlsConstants::LayerArmRightLocalSpaceCurveName(), 0.0f},
		{UAlsConstants::LayerHandLeftCurveName(), 0.0f},
		{UAlsConstants::LayerHandRightCurveName(), 0.0f},
		{UAlsConstants::LayerSpineCurveName(), 1.0f},
		{UAlsConstants::LayerSpineAdditiveCurveName(), 0.0f},
		{UAlsConstants::LayerPelvisCurveName(), 0.0f},
		{UAlsConstants::LayerLegsCurveName(), 0.0f},

		{UAlsConstants::HandLeftIkCurveName(), 0.0f},
		{UAlsConstants::HandRightIkCurveName(), 0.0f},

		{UAlsConstants::ViewBlockCurveName(), 0.0f},
		{UAlsConstants::AllowAimingCurveName(), 1.0f},

		{UAlsConstants::HipsDirectionLockCurveName(), 0.0f},
	};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="添加插槽曲线")
	uint8 bAddSlotCurves : 1 {false};

	// 插槽曲线名称及其默认值
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="插槽曲线名称")
	TMap<FName, float> SlotCurveNames
	{
		{UAlsConstants::LayerHeadSlotCurveName(), 0.0f},
		{UAlsConstants::LayerArmLeftSlotCurveName(), 1.0f},
		{UAlsConstants::LayerArmRightSlotCurveName(), 1.0f},
		{UAlsConstants::LayerSpineSlotCurveName(), 0.0f},
		{UAlsConstants::LayerPelvisSlotCurveName(), 0.0f},
		{UAlsConstants::LayerLegsSlotCurveName(), 0.0f},
		{UAlsConstants::CurvesCurveName(),1.0f}
	};

public:
	virtual void OnApply_Implementation(UAnimSequence* Sequence) override;

private:
	void CreateCurves(UAnimSequence* Sequence, const TMap<FName, float>& Curves) const;
};
