#pragma once
#include  "AlsSpineRotationState.generated.h"

// USTRUCT()
// struct FSpineRotationState
// {
// 	GENERATED_BODY()
// 	
// };

UENUM(BlueprintType)
enum class ESpineRotationState : uint8
{
	Unknown     UMETA(DisplayName = "Unknown"),
	YawOnly     UMETA(DisplayName = "Yaw Only"),
	PitchOnly   UMETA(DisplayName = "Pitch Only"),
	YawAndPitch UMETA(DisplayName = "Yaw and Pitch"),
};