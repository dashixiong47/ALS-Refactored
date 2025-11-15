#include "Modifiers/AlsAnimationModifier_CreateLayeringCurves.h"

#include "Animation/AnimSequence.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsAnimationModifier_CreateLayeringCurves)

void UAlsAnimationModifier_CreateLayeringCurves::OnApply_Implementation(UAnimSequence* Sequence)
{
	Super::OnApply_Implementation(Sequence);

	CreateCurves(Sequence, CurveNames);

	if (bAddSlotCurves)
	{
		CreateCurves(Sequence, SlotCurveNames);
	}
}

void UAlsAnimationModifier_CreateLayeringCurves::CreateCurves(
	UAnimSequence* Sequence,
	const TMap<FName, float>& Curves
) const
{
	// 遍历Map，每个元素包含 {曲线名, 默认值}
	for (const auto& Pair : Curves)
	{
		const FName& CurveName = Pair.Key;
		const float Value = Pair.Value;

		// 检查曲线是否已经存在
		if (UAnimationBlueprintLibrary::DoesCurveExist(Sequence, CurveName, ERawCurveTrackTypes::RCT_Float))
		{
			// 如果不允许覆盖现有曲线，就跳过
			if (!bOverrideExistingCurves)
			{
				continue;
			}

			// 否则移除旧曲线
			UAnimationBlueprintLibrary::RemoveCurve(Sequence, CurveName);
		}

		// 添加新的空曲线
		UAnimationBlueprintLibrary::AddCurve(Sequence, CurveName);

		// 根据设置决定是否在每帧都加Key
		if (bAddKeyOnEachFrame)
		{
			for (int32 i = 0; i < Sequence->GetNumberOfSampledKeys(); i++)
			{
				UAnimationBlueprintLibrary::AddFloatCurveKey(
					Sequence,
					CurveName,
					Sequence->GetTimeAtFrame(i),
					Value
				);
			}
		}
		else
		{
			// 只在第一帧加一个Key
			UAnimationBlueprintLibrary::AddFloatCurveKey(
				Sequence,
				CurveName,
				Sequence->GetTimeAtFrame(0),
				Value
			);
		}
	}
}


