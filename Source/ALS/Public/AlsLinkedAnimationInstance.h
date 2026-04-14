#pragma once

#include "Animation/AnimInstance.h"
#include "AlsLinkedAnimationInstance.generated.h"

enum class EAlsHipsDirection : uint8;
class UAlsAnimationInstance;
class AAlsCharacter;

UCLASS()
class ALS_API UAlsLinkedAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, Category = "ALS|链接动画实例|状态", Transient,
		Meta = (DisplayName = "父动画实例", ToolTip = "当前链接动画实例对应的父 ALS 动画实例。"))
	TWeakObjectPtr<UAlsAnimationInstance> Parent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|链接动画实例|状态", Transient,
		Meta = (DisplayName = "角色", ToolTip = "当前链接动画实例所驱动的 ALS 角色。"))
	TObjectPtr<AAlsCharacter> Character;

public:
	UAlsLinkedAnimationInstance();

	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

protected:
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;

protected:
	// Be very careful when using this function to read your custom variables using the property access system. It is
	// safe to use this function to read variables that change only inside UAlsAnimationInstance::NativeUpdateAnimation()
	// because it is guaranteed that this function will be called before parallel animation evaluation. Reading
	// variables that change in other functions can be dangerous because they can be changed in the game thread
	// at the same time as being read in the worker thread, which can lead to undefined behavior or even a crash.
	UFUNCTION(BlueprintPure, Category = "ALS|Linked Animation Instance",
		Meta = (BlueprintThreadSafe, ReturnDisplayName = "Parent"))
	UAlsAnimationInstance* GetParent() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeHead();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshHead();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeLean();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeGrounded();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshGrounded();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void ResetGroundedEntryMode();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshGroundedMovement();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void SetHipsDirection(EAlsHipsDirection NewHipsDirection);

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeStandingMovement();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshStandingMovement();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void ResetPivot();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshCrouchingMovement();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshInAir();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshDynamicTransitions();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshRotateInPlace();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeTurnInPlace();

	UFUNCTION(BlueprintCallable, Category = "ALS|Linked Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshTurnInPlace();
};

inline UAlsAnimationInstance* UAlsLinkedAnimationInstance::GetParent() const
{
	return Parent.Get();
}
