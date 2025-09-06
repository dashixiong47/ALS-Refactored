#pragma once

#include "AnimationModifier.h"
#include "Utility/AlsConstants.h"
#include "AlsAnimationModifier_CreateCurves.generated.h"
USTRUCT(BlueprintType)
struct ALSEDITOR_API FAlsAnimationCurveKey
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", Meta = (ClampMin = 0), DisplayName="帧")
	int32 Frame{0};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="值")
	float Value{0.0f};
};

USTRUCT(BlueprintType)
struct ALSEDITOR_API FAlsAnimationCurve
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="曲线名称")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="每帧添加关键点")
	uint8 bAddKeyOnEachFrame : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="关键帧")
	TArray<FAlsAnimationCurveKey> Keys
	{
			{0, 0.0f}
	};
};

UCLASS(DisplayName = "Als Create Curves Animation Modifier")
class ALSEDITOR_API UAlsAnimationModifier_CreateCurves : public UAnimationModifier
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="覆盖已有曲线")
	uint8 bOverrideExistingCurves : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="曲线列表")
	TArray<FAlsAnimationCurve> Curves
	{
			{UAlsConstants::PoseGaitCurveName()},
			{UAlsConstants::PoseMovingCurveName()},
			{UAlsConstants::PoseStandingCurveName()},
			{UAlsConstants::PoseCrouchingCurveName()},
			{UAlsConstants::PoseInAirCurveName()},
			{UAlsConstants::PoseGroundedCurveName()},

			{UAlsConstants::FootLeftIkCurveName()},
			{UAlsConstants::FootLeftLockCurveName()},
			{UAlsConstants::FootRightIkCurveName()},
			{UAlsConstants::FootRightLockCurveName()},
			{UAlsConstants::FootPlantedCurveName()},
			{UAlsConstants::FeetCrossingCurveName()},

			{UAlsConstants::AllowTransitionsCurveName()},
			{UAlsConstants::SprintBlockCurveName()},
			{UAlsConstants::GroundPredictionBlockCurveName()},
			{UAlsConstants::FootstepSoundBlockCurveName()}
	};

public:
	virtual void OnApply_Implementation(UAnimSequence* Sequence) override;
};
