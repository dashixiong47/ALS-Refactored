#pragma once

#include "Animation/AnimNodeBase.h"
#include "AlsAnimNode_CurvesBlend.generated.h"

UENUM(BlueprintType)
enum class EAlsCurvesBlendMode : uint8
{
	// Use the base pose. Same as ECurveBlendOption::UseBasePose.
	DoNotBlend,
	// Add curves from the curve pose, multiplied by the blend amount, to curves from the base pose. Same as ECurveBlendOption::BlendByWeight.
	Accumulate,
	// Interpolate curves between the base pose and the curve pose the using blend amount as alpha.
	Lerp,
	// Curves from the curve pose will take precedence over the same curves from the base bose. Same as ECurveBlendOption::Override.
	Combine,
	// Curves from the base pose will take precedence over the same curves from the curve pose. Same as ECurveBlendOption::DoNotOverride.
	CombinePreserved,
	// Find the highest curve values from poses and use them. Same as ECurveBlendOption::UseMaxValue.
	UseMaxValue,
	// Find the lowest curve values from poses and use them. Same as  ECurveBlendOption::UseMinValue.
	UseMinValue,
	// Completely override curves from the base pose with curves from the curve pose, multiplied by the blend amount.
	Override
};

USTRUCT(BlueprintInternalUseOnly)
struct ALS_API FAlsAnimNode_CurvesBlend : public FAnimNode_Base
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动画节点|设置",
		Meta = (DisplayName = "基础姿势", ToolTip = "曲线混合使用的基础姿势。"))
	FPoseLink BasePose;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|动画节点|设置",
		Meta = (DisplayName = "曲线姿势", ToolTip = "用于提供曲线值的姿势。"))
	FPoseLink CurvePose;

protected:
	UPROPERTY(EditAnywhere, Category = "ALS|动画节点|设置",
		Meta = (ClampMin = 0, ClampMax = 1, PinShownByDefault, DisplayName = "混合量", ToolTip = "基础姿势与曲线姿势之间的混合权重。"))
	float BlendAmount{1.0f};

	UPROPERTY(EditAnywhere, Category = "ALS|动画节点|设置",
		Meta = (DisplayName = "混合模式", ToolTip = "曲线混合时采用的模式。"))
	EAlsCurvesBlendMode BlendMode{EAlsCurvesBlendMode::Accumulate};

public:
	virtual void Initialize_AnyThread(const FAnimationInitializeContext& Context) override;

	virtual void CacheBones_AnyThread(const FAnimationCacheBonesContext& Context) override;

	virtual void Update_AnyThread(const FAnimationUpdateContext& Context) override;

	virtual void Evaluate_AnyThread(FPoseContext& Output) override;

	virtual void GatherDebugData(FNodeDebugData& DebugData) override;
};
