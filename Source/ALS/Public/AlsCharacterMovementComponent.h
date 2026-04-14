#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "Settings/AlsMovementSettings.h"
#include "AlsCharacterMovementComponent.generated.h"

using FAlsPhysicsRotationDelegate = TMulticastDelegate<void(float DeltaTime)>;

class ALS_API FAlsCharacterNetworkMoveData : public FCharacterNetworkMoveData
{
private:
	using Super = FCharacterNetworkMoveData;

public:
	FGameplayTag RotationMode{AlsRotationModeTags::ViewDirection};

	FGameplayTag Stance{AlsStanceTags::Standing};

	FGameplayTag MaxAllowedGait{AlsGaitTags::Running};

public:
	virtual void ClientFillNetworkMoveData(const FSavedMove_Character& Move, ENetworkMoveType MoveType) override;

	virtual bool Serialize(UCharacterMovementComponent& Movement, FArchive& Archive, UPackageMap* Map, ENetworkMoveType MoveType) override;
};

class ALS_API FAlsCharacterNetworkMoveDataContainer : public FCharacterNetworkMoveDataContainer
{
public:
	TStaticArray<FAlsCharacterNetworkMoveData, 3> MoveData;

public:
	FAlsCharacterNetworkMoveDataContainer();
};

class ALS_API FAlsSavedMove : public FSavedMove_Character
{
private:
	using Super = FSavedMove_Character;

public:
	FGameplayTag RotationMode{AlsRotationModeTags::ViewDirection};

	FGameplayTag Stance{AlsStanceTags::Standing};

	FGameplayTag MaxAllowedGait{AlsGaitTags::Running};

public:
	virtual void Clear() override;

	virtual void SetMoveFor(ACharacter* Character, float NewDeltaTime, const FVector& NewAcceleration,
	                        FNetworkPredictionData_Client_Character& PredictionData) override;

	virtual bool CanCombineWith(const FSavedMovePtr& NewMovePtr, ACharacter* Character, float MaxDeltaTime) const override;

	virtual void CombineWith(const FSavedMove_Character* PreviousMove, ACharacter* Character,
	                         APlayerController* Player, const FVector& PreviousStartLocation) override;

	virtual void PrepMoveFor(ACharacter* Character) override;
};

class ALS_API FAlsNetworkPredictionData : public FNetworkPredictionData_Client_Character
{
private:
	using Super = FNetworkPredictionData_Client_Character;

public:
	explicit FAlsNetworkPredictionData(const UCharacterMovementComponent& Movement);

	virtual FSavedMovePtr AllocateNewMove() override;
};

UCLASS(ClassGroup = "ALS")
class ALS_API UAlsCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	friend FAlsSavedMove;

public:
	// If checked, improves the response to interaction from moving kinematic physical
	// bodies, but may cause some issues when interacting with simulated physical bodies.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|移动组件|设置",
		Meta = (DisplayName = "允许改进穿透修正", ToolTip = "启用后会改善与运动学刚体交互时的穿透修正，但可能对模拟物理体带来副作用。"))
	uint8 bAllowImprovedPenetrationAdjustment : 1 {true};

protected:
	FAlsCharacterNetworkMoveDataContainer MoveDataContainer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "移动设置", ToolTip = "当前移动组件正在使用的 ALS 移动设置。"))
	TObjectPtr<UAlsMovementSettings> MovementSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "步态设置", ToolTip = "当前步态对应的移动参数设置。"))
	FAlsMovementGaitSettings GaitSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "旋转模式", ToolTip = "移动组件当前使用的旋转模式。"))
	FGameplayTag RotationMode{AlsRotationModeTags::ViewDirection};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "姿态", ToolTip = "移动组件当前使用的姿态。"))
	FGameplayTag Stance{AlsStanceTags::Standing};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "最大允许步态", ToolTip = "当前可使用的最高步态。"))
	FGameplayTag MaxAllowedGait{AlsGaitTags::Running};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (ClampMin = 0, ClampMax = 3, DisplayName = "步态强度", ToolTip = "用于动画表现的步态强度值。"))
	float GaitAmount{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (ClampMin = 0, ForceUnits = "cm/s^2", DisplayName = "最大步行加速度", ToolTip = "当前步行状态下的最大加速度。"))
	float MaxAccelerationWalking{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "移动模式已锁定", ToolTip = "是否临时锁定移动模式切换。"))
	uint8 bMovementModeLocked : 1 {false};

	// Used to temporarily prohibit the player from moving the character. Also works for AI-controlled characters.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "输入已阻止", ToolTip = "是否临时阻止角色响应输入移动。对 AI 角色同样有效。"))
	uint8 bInputBlocked : 1 {false};

	// Valid only on locally controlled characters.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "上一次控制器旋转", ToolTip = "仅对本地控制角色有效，记录上一帧控制器旋转。"))
	FRotator PreviousControlRotation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "穿透修正前速度", ToolTip = "执行穿透修正前缓存的速度。"))
	FVector PrePenetrationAdjustmentVelocity{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|移动组件|状态", Transient,
		Meta = (DisplayName = "穿透修正前速度有效", ToolTip = "是否存在有效的穿透修正前速度缓存。"))
	uint8 bPrePenetrationAdjustmentVelocityValid : 1 {false};

public:
	FAlsPhysicsRotationDelegate OnPhysicsRotation;

public:
	UAlsCharacterMovementComponent();

#if WITH_EDITOR
	virtual bool CanEditChange(const FProperty* Property) const override;
#endif

	virtual void BeginPlay() override;

	virtual FVector ConsumeInputVector() override;

	virtual void SetMovementMode(EMovementMode NewMovementMode, uint8 NewCustomMode = 0) override;

	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;

	virtual bool ShouldPerformAirControlForPathFollowing() const override;

	virtual void UpdateBasedRotation(FRotator& FinalRotation, const FRotator& ReducedRotation) override;

	virtual bool ApplyRequestedMove(float DeltaTime, float CurrentMaxAcceleration, float MaxSpeed, float Friction,
	                                float BrakingDeceleration, FVector& RequestedAcceleration, float& RequestedSpeed) override;

	virtual void CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration) override;

	virtual float GetMaxAcceleration() const override;

protected:
	virtual void ControlledCharacterMove(const FVector& InputVector, float DeltaTime) override;

public:
	virtual void PhysicsRotation(float DeltaTime) override;

	// ReSharper disable once CppRedefinitionOfDefaultArgumentInOverrideFunction
	virtual void MoveSmooth(const FVector& InVelocity, float DeltaTime, FStepDownResult* StepDownResult = nullptr) override;

protected:
	virtual void PhysWalking(float DeltaTime, int32 IterationsCount) override;

	virtual void PhysNavWalking(float DeltaTime, int32 IterationsCount) override;

	virtual void PhysCustom(float DeltaTime, int32 IterationsCount) override;

public:
	virtual void ComputeFloorDist(const FVector& CapsuleLocation, float LineDistance, float SweepDistance, FFindFloorResult& OutFloorResult,
	                              float SweepRadius, const FHitResult* DownwardSweepResult) const override;

protected:
	virtual void PerformMovement(float DeltaTime) override;

public:
	virtual FNetworkPredictionData_Client* GetPredictionData_Client() const override;

protected:
	virtual void SmoothClientPosition(float DeltaTime) override;

	virtual void MoveAutonomous(float ClientTimeStamp, float DeltaTime, uint8 CompressedFlags, const FVector& NewAcceleration) override;

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|Character Movement")
	void SetMovementSettings(UAlsMovementSettings* NewMovementSettings);

	const FAlsMovementGaitSettings& GetGaitSettings() const;

private:
	void RefreshGaitSettings();

public:
	FGameplayTag GetRotationMode() const;

	void SetRotationMode(FGameplayTag NewRotationMode);

	FGameplayTag GetStance() const;

	void SetStance(FGameplayTag NewStance);

	FGameplayTag GetMaxAllowedGait() const;

	void SetMaxAllowedGait(FGameplayTag NewMaxAllowedGait);

	// Returns the character's current speed, mapped to the speed ranges from the movement settings.
	// Varies from 0 to 3, where 0 is stopped, 1 is walking, 2 is running, and 3 is sprinting.
	float GetGaitAmount() const;

private:
	void RefreshGroundedMovementSettings();

public:
	void SetMovementModeLocked(bool bNewMovementModeLocked);

	void SetInputBlocked(bool bNewInputBlocked);

	bool TryConsumePrePenetrationAdjustmentVelocity(FVector& OutVelocity);
};

inline const FAlsMovementGaitSettings& UAlsCharacterMovementComponent::GetGaitSettings() const
{
	return GaitSettings;
}

inline FGameplayTag UAlsCharacterMovementComponent::GetRotationMode() const
{
	return RotationMode;
}

inline FGameplayTag UAlsCharacterMovementComponent::GetStance() const
{
	return Stance;
}

inline FGameplayTag UAlsCharacterMovementComponent::GetMaxAllowedGait() const
{
	return MaxAllowedGait;
}

inline void UAlsCharacterMovementComponent::SetMaxAllowedGait(FGameplayTag NewMaxAllowedGait)
{
	MaxAllowedGait = NewMaxAllowedGait;
}

inline float UAlsCharacterMovementComponent::GetGaitAmount() const
{
	return GaitAmount;
}
