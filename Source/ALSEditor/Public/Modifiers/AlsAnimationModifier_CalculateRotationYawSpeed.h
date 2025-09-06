#pragma once

#include "AnimationModifier.h"
#include "AlsAnimationModifier_CalculateRotationYawSpeed.generated.h"

// 这个 Animation Modifier 用于计算根骨骼的旋转速度，用来生成旋转动画的 Yaw Speed 曲线。
// 每个曲线值表示当前帧与下一帧之间的旋转速度，可用于驱动角色旋转，模拟 Root Motion 效果。
UCLASS(DisplayName = "Als Calculate Rotation Yaw Speed Animation Modifier")
class ALSEDITOR_API UAlsAnimationModifier_CalculateRotationYawSpeed : public UAnimationModifier
{
	GENERATED_BODY()

public:
	// 应用 Animation Modifier 时的逻辑实现
	virtual void OnApply_Implementation(UAnimSequence* Sequence) override;
};

