#pragma once

#include "AlsInAirRotationMode.generated.h"

UENUM(BlueprintType)
enum class EAlsInAirRotationMode : uint8
{
	// 跳跃时旋转朝向速度方向
	RotateToVelocityOnJump UMETA(DisplayName = "跳跃时旋转朝向速度方向"),

	// 保持相对旋转
	KeepRelativeRotation UMETA(DisplayName = "保持相对旋转"),

	// 保持世界旋转
	KeepWorldRotation UMETA(DisplayName = "保持世界旋转")
};

