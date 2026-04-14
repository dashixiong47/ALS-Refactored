#pragma once

#include "Animation/AnimInstance.h"
#include "Engine/World.h"
#include "State/AlsControlRigInput.h"
#include "State/AlsCrouchingState.h"
#include "State/AlsDynamicTransitionsState.h"
#include "State/AlsFeetState.h"
#include "State/AlsGroundedState.h"
#include "State/AlsHeadState.h"
#include "State/AlsInAirState.h"
#include "State/AlsLayeringState.h"
#include "State/AlsLeanState.h"
#include "State/AlsLocomotionAnimationState.h"
#include "State/AlsMovementBaseState.h"
#include "State/AlsPoseState.h"
#include "State/AlsRagdollingAnimationState.h"
#include "State/AlsRotateInPlaceState.h"
#include "State/AlsSpineState.h"
#include "State/AlsStandingState.h"
#include "State/AlsTransitionsState.h"
#include "State/AlsTurnInPlaceState.h"
#include "State/AlsViewAnimationState.h"
#include "Utility/AlsGameplayTags.h"
#include "AlsAnimationInstance.generated.h"

class UAlsLinkedAnimationInstance;
class UAlsAnimationInstanceSettings;
class AAlsCharacter;

UCLASS()
class ALS_API UAlsAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

	friend UAlsLinkedAnimationInstance;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|设置",
		Meta = (DisplayName = "动画实例设置", ToolTip = "ALS 动画实例使用的设置数据资产。"))
	TObjectPtr<UAlsAnimationInstanceSettings> Settings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "角色", ToolTip = "当前动画实例所驱动的 ALS 角色。"))
	TObjectPtr<AAlsCharacter> Character;

	// Used to indicate that the animation instance has not been updated for a long time
	// and its current state may not be correct (such as foot location used in foot lock).
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "待更新", ToolTip = "是否需要在下一帧重新完整刷新动画状态。"))
	uint8 bPendingUpdate : 1 {true};

	// Time of the last teleportation event.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (ClampMin = 0, DisplayName = "最近传送时间", ToolTip = "最近一次触发传送事件的时间。"))
	double TeleportedTime{0.0f};

#if WITH_EDITORONLY_DATA
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "显示调试轨迹", ToolTip = "是否显示 ALS 动画调试轨迹。"))
	uint8 bDisplayDebugTraces : 1 {false};

	mutable TArray<TFunction<void()>> DisplayDebugTracesQueue;
#endif

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "视角模式", ToolTip = "动画实例当前读取到的视角模式。"))
	FGameplayTag ViewMode{AlsViewModeTags::ThirdPerson};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "移动模式", ToolTip = "动画实例当前读取到的移动模式。"))
	FGameplayTag LocomotionMode{AlsLocomotionModeTags::Grounded};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "旋转模式", ToolTip = "动画实例当前读取到的旋转模式。"))
	FGameplayTag RotationMode{AlsRotationModeTags::ViewDirection};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "姿态", ToolTip = "动画实例当前读取到的姿态。"))
	FGameplayTag Stance{AlsStanceTags::Standing};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "步态", ToolTip = "动画实例当前读取到的步态。"))
	FGameplayTag Gait{AlsGaitTags::Walking};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "叠加模式", ToolTip = "动画实例当前读取到的叠加模式。"))
	FGameplayTag OverlayMode{AlsOverlayModeTags::Default};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "移动动作", ToolTip = "动画实例当前读取到的特殊移动动作标签。"))
	FGameplayTag LocomotionAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "地面进入模式", ToolTip = "角色进入地面移动时使用的入口模式标签。"))
	FGameplayTag GroundedEntryMode;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "移动基底状态", ToolTip = "动画实例缓存的移动基底状态。"))
	FAlsMovementBaseState MovementBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "分层状态", ToolTip = "ALS 动画分层相关状态。"))
	FAlsLayeringState LayeringState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "姿势状态", ToolTip = "ALS 当前姿势混合相关状态。"))
	FAlsPoseState PoseState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "视角动画状态", ToolTip = "ALS 视角相关的动画状态。"))
	FAlsViewAnimationState ViewState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "脊椎状态", ToolTip = "ALS 脊椎旋转与混合状态。"))
	FAlsSpineState SpineState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "头部状态", ToolTip = "ALS 头部朝向相关状态。"))
	FAlsHeadState HeadState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "移动动画状态", ToolTip = "ALS 当前移动动画状态数据。"))
	FAlsLocomotionAnimationState LocomotionState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "倾斜状态", ToolTip = "ALS 当前角色倾斜相关状态。"))
	FAlsLeanState LeanState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "地面状态", ToolTip = "ALS 当前地面移动相关状态。"))
	FAlsGroundedState GroundedState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "站立状态", ToolTip = "ALS 当前站立移动相关状态。"))
	FAlsStandingState StandingState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "蹲伏状态", ToolTip = "ALS 当前蹲伏移动相关状态。"))
	FAlsCrouchingState CrouchingState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "空中状态", ToolTip = "ALS 当前空中移动相关状态。"))
	FAlsInAirState InAirState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "脚部状态", ToolTip = "ALS 当前脚步落点与锁定相关状态。"))
	FAlsFeetState FeetState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "过渡状态", ToolTip = "ALS 当前动画过渡相关状态。"))
	FAlsTransitionsState TransitionsState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "动态过渡状态", ToolTip = "ALS 当前动态过渡相关状态。"))
	FAlsDynamicTransitionsState DynamicTransitionsState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "原地旋转状态", ToolTip = "ALS 当前原地旋转状态。"))
	FAlsRotateInPlaceState RotateInPlaceState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "转身状态", ToolTip = "ALS 当前转身状态。"))
	FAlsTurnInPlaceState TurnInPlaceState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|动画实例|状态", Transient,
		Meta = (DisplayName = "布娃娃动画状态", ToolTip = "ALS 当前布娃娃动画相关状态。"))
	FAlsRagdollingAnimationState RagdollingState;

public:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaTime) override;

	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

	virtual void NativePostUpdateAnimation();

protected:
	virtual FAnimInstanceProxy* CreateAnimInstanceProxy() override;

	// Core

protected:
	UFUNCTION(BlueprintPure, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe, ReturnDisplayName = "Setting"))
	UAlsAnimationInstanceSettings* GetSettingsUnsafe() const;

	UFUNCTION(BlueprintPure, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe, ReturnDisplayName = "Rig Input"))
	FAlsControlRigInput GetControlRigInput() const;

public:
	void MarkPendingUpdate();

	void MarkTeleported();

private:
	void RefreshMovementBaseOnGameThread();

	void RefreshLayering();

	void RefreshPose();

	// View

private:
	void RefreshViewOnGameThread();

	void RefreshView(float DeltaTime);

	// Spine

public:
	virtual bool IsSpineRotationAllowed();

private:
	void RefreshSpine(float SpineBlendAmount, float DeltaTime);

	// Head

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeHead();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshHead();

	// Locomotion

private:
	void RefreshLocomotionOnGameThread();

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeLean();

	// Grounded

public:
	void SetGroundedEntryMode(FGameplayTag NewGroundedEntryMode);

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void ResetGroundedEntryMode();

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeGrounded();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshGrounded();

private:
	FVector3f GetRelativeVelocity() const;

	FVector2f GetRelativeAccelerationAmount() const;

	void RefreshVelocityBlend();

	void RefreshGroundedLean();

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshGroundedMovement();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void SetHipsDirection(EAlsHipsDirection NewHipsDirection);

private:
	void RefreshMovementDirection(float ViewRelativeVelocityYawAngle);

	void RefreshRotationYawOffsets(float ViewRelativeVelocityYawAngle);

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeStandingMovement();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshStandingMovement();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void ActivatePivot();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void ResetPivot();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshCrouchingMovement();

	// In Air

public:
	void Jump();

private:
	void RefreshInAirOnGameThread();

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshInAir();

	void RefreshGroundPrediction();

	void RefreshInAirLean();

	// Feet

private:
	void RefreshFeetOnGameThread();

	void RefreshFeet(float DeltaTime);

	void ProcessFootLockTeleport(const FAlsFootUpdateContext& Context) const;

	void ProcessFootLockBaseChange(const FAlsFootUpdateContext& Context) const;

	void RefreshFootLock(const FAlsFootUpdateContext& Context) const;

	// Transitions

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void PlayQuickStopAnimation();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void PlayTransitionAnimation(UAnimSequenceBase* Sequence, float BlendInDuration = 0.2f, float BlendOutDuration = 0.2f,
	                             float PlayRate = 1.0f, float StartTime = 0.0f, bool bFromStandingIdleOnly = false);

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void PlayTransitionLeftAnimation(float BlendInDuration = 0.2f, float BlendOutDuration = 0.2f, float PlayRate = 1.0f,
	                                 float StartTime = 0.0f, bool bFromStandingIdleOnly = false);

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void PlayTransitionRightAnimation(float BlendInDuration = 0.2f, float BlendOutDuration = 0.2f, float PlayRate = 1.0f,
	                                  float StartTime = 0.0f, bool bFromStandingIdleOnly = false);

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void StopTransitionAndTurnInPlaceAnimations(float BlendOutDuration = -1.0f);

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshDynamicTransitions();

private:
	void RefreshTransitions();

	void PlayQueuedTransitionAnimation();

	void StopQueuedTransitionAndTurnInPlaceAnimations();

	// Rotate In Place

public:
	virtual bool IsRotateInPlaceAllowed();

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshRotateInPlace();

	// Turn In Place

public:
	virtual bool IsTurnInPlaceAllowed();

protected:
	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void InitializeTurnInPlace();

	UFUNCTION(BlueprintCallable, Category = "ALS|Animation Instance", Meta = (BlueprintThreadSafe))
	void RefreshTurnInPlace();

private:
	void PlayQueuedTurnInPlaceAnimation();

	// Ragdolling

private:
	void RefreshRagdollingOnGameThread();

public:
	FPoseSnapshot& SnapshotFinalRagdollPose();

	// Utility

public:
	float GetCurveValueClamped01(FName CurveName) const;
};

inline UAlsAnimationInstanceSettings* UAlsAnimationInstance::GetSettingsUnsafe() const
{
	return Settings;
}

inline void UAlsAnimationInstance::MarkPendingUpdate()
{
	bPendingUpdate |= true;
}

inline void UAlsAnimationInstance::MarkTeleported()
{
	TeleportedTime = GetWorld()->GetTimeSeconds();
}

inline void UAlsAnimationInstance::SetGroundedEntryMode(const FGameplayTag NewGroundedEntryMode)
{
	GroundedEntryMode = NewGroundedEntryMode;
}

inline void UAlsAnimationInstance::ResetGroundedEntryMode()
{
	GroundedEntryMode = FGameplayTag::EmptyTag;
}

inline void UAlsAnimationInstance::SetHipsDirection(const EAlsHipsDirection NewHipsDirection)
{
	GroundedState.HipsDirection = NewHipsDirection;
}

inline void UAlsAnimationInstance::ResetPivot()
{
	StandingState.bPivotActive = false;
}

inline void UAlsAnimationInstance::Jump()
{
	InAirState.bJumpRequested = true;
}
