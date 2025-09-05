#pragma once

#include "AlsCrouchingSettings.h"
#include "AlsDynamicTransitionsSettings.h"
#include "AlsFeetSettings.h"
#include "AlsGeneralAnimationSettings.h"
#include "AlsGroundedSettings.h"
#include "AlsInAirSettings.h"
#include "AlsRotateInPlaceSettings.h"
#include "AlsStandingSettings.h"
#include "AlsTransitionsSettings.h"
#include "AlsTurnInPlaceSettings.h"
#include "AlsViewAnimationSettings.h"
#include "Engine/DataAsset.h"
#include "AlsAnimationInstanceSettings.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsAnimationInstanceSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="通用动画设置")
	FAlsGeneralAnimationSettings General;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="视角动画设置")
	FAlsViewAnimationSettings View;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="地面状态设置")
	FAlsGroundedSettings Grounded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="站立设置")
	FAlsStandingSettings Standing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="蹲伏设置")
	FAlsCrouchingSettings Crouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="空中状态设置")
	FAlsInAirSettings InAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="脚部设置")
	FAlsFeetSettings Feet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="过渡设置")
	FAlsTransitionsSettings Transitions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="动态过渡设置")
	FAlsDynamicTransitionsSettings DynamicTransitions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="原地旋转设置")
	FAlsRotateInPlaceSettings RotateInPlace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="原地转向设置")
	FAlsGeneralTurnInPlaceSettings TurnInPlace;


public:
	UAlsAnimationInstanceSettings();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
};
