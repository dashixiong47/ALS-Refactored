#pragma once

#include "AnimationModifier.h"
#include "AlsAnimationModifier_CopyCurves.generated.h"

UCLASS(DisplayName = "Als Copy Curves Animation Modifier")
class ALSEDITOR_API UAlsAnimationModifier_CopyCurves : public UAnimationModifier
{
	GENERATED_BODY()

protected:
	// 要拷贝曲线的源动画序列
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="源动画序列")
	TSoftObjectPtr<UAnimSequence> SourceSequence;

	// 是否拷贝所有曲线
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="拷贝所有曲线")
	uint8 bCopyAllCurves : 1 {true};

	// 仅在不拷贝所有曲线时生效，指定需要拷贝的曲线名
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="曲线名称列表",
		Meta = (EditCondition = "!bCopyAllCurves"))
	TArray<FName> CurveNames;

public:
	virtual void OnApply_Implementation(UAnimSequence* Sequence) override;

private:
	// 执行曲线拷贝的静态方法
	static void CopyCurve(UAnimSequence* SourceSequence, UAnimSequence* TargetSequence, const FName& CurveName);
};
