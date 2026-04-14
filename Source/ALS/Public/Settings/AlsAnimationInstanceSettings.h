#pragma once

#include "AlsCrouchingSettings.h"
#include "AlsDynamicTransitionsSettings.h"
#include "AlsFeetSettings.h"
#include "AlsGeneralAnimationSettings.h"
#include "AlsGroundedSettings.h"
#include "AlsHeadSettings.h"
#include "AlsInAirSettings.h"
#include "AlsRotateInPlaceSettings.h"
#include "AlsStandingSettings.h"
#include "AlsTransitionsSettings.h"
#include "AlsTurnInPlaceSettings.h"
#include "Engine/DataAsset.h"
#include "AlsAnimationInstanceSettings.generated.h"

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsAnimationInstanceSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "通用设置", ToolTip = "ALS 动画实例的通用动画设置。"))
	FAlsGeneralAnimationSettings General;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "头部设置", ToolTip = "ALS 头部朝向与插值相关设置。"))
	FAlsHeadSettings Head;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "地面设置", ToolTip = "ALS 地面移动相关动画设置。"))
	FAlsGroundedSettings Grounded;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "站立设置", ToolTip = "ALS 站立移动相关动画设置。"))
	FAlsStandingSettings Standing;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "蹲伏设置", ToolTip = "ALS 蹲伏移动相关动画设置。"))
	FAlsCrouchingSettings Crouching;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "空中设置", ToolTip = "ALS 空中动画与落地预测相关设置。"))
	FAlsInAirSettings InAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "脚部设置", ToolTip = "ALS 脚步锁定与脚 IK 相关设置。"))
	FAlsFeetSettings Feet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "过渡设置", ToolTip = "ALS 过渡动画相关设置。"))
	FAlsTransitionsSettings Transitions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "动态过渡设置", ToolTip = "ALS 动态过渡动画相关设置。"))
	FAlsDynamicTransitionsSettings DynamicTransitions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "原地旋转设置", ToolTip = "ALS 原地旋转相关设置。"))
	FAlsRotateInPlaceSettings RotateInPlace;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画设置",
		Meta = (DisplayName = "转身设置", ToolTip = "ALS 原地转身相关设置。"))
	FAlsGeneralTurnInPlaceSettings TurnInPlace;

public:
	UAlsAnimationInstanceSettings();

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
};
