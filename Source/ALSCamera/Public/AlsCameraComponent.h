#pragma once

#include "Components/SkeletalMeshComponent.h"
#include "Utility/AlsMath.h"
#include "AlsCameraComponent.generated.h"

class UAlsCameraSettings;
class ACharacter;

UCLASS(ClassGroup = "ALS", Meta = (BlueprintSpawnableComponent),
	HideCategories = ("ComponentTick", "Clothing", "Physics", "MasterPoseComponent", "Collision", "AnimationRig",
		"Lighting", "Deformer", "Rendering", "PathTracing", "HLOD", "Navigation", "VirtualTexture", "SkeletalMesh",
		"LeaderPoseComponent", "Optimization", "LOD", "MaterialParameters", "TextureStreaming", "Mobile", "RayTracing"))
class ALSCAMERA_API UAlsCameraComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="相机设置")
	TObjectPtr<UAlsCameraSettings> Settings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (InlineEditConditionToggle),
		DisplayName="覆盖视野(FOV)")
	uint8 bOverrideFieldOfView : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings",
		Meta = (ClampMin = 5, ClampMax = 175, EditCondition = "bOverrideFieldOfView", ForceUnits = "deg"),
		DisplayName="自定义视野(FOV)")
	float FieldOfViewOverride{90.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", Meta = (ClampMin = 0, ClampMax = 1),
		DisplayName="后处理权重")
	float PostProcessWeight{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="角色")
	TObjectPtr<ACharacter> Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Meta = (ShowInnerProperties),
		DisplayName="动画实例")
	TWeakObjectPtr<UAnimInstance> AnimationInstance;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, Meta = (ForceUnits = "x"),
		DisplayName="上一帧全局时间缩放")
	float PreviousGlobalTimeDilation{1.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="枢轴目标位置")
	FVector PivotTargetLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="枢轴滞后位置")
	FVector PivotLagLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="枢轴位置")
	FVector PivotLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="相机位置")
	FVector CameraLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="相机旋转")
	FRotator CameraRotation{ForceInit};

	UPROPERTY(BlueprintReadOnly, Category = "State", Transient, DisplayName="移动基底组件")
	TObjectPtr<UPrimitiveComponent> MovementBasePrimitive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="移动基底骨骼名")
	FName MovementBaseBoneName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="枢轴相对滞后位置")
	FVector PivotMovementBaseRelativeLagLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="相机相对旋转(移动基底)")
	FQuat CameraMovementBaseRelativeRotation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient,
		Meta = (ClampMin = 0, ClampMax = 1, ForceUnits = "%"), DisplayName="追踪距离比例")
	float TraceDistanceRatio{1.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient,
		Meta = (ClampMin = 5, ClampMax = 175, ForceUnits = "deg"), DisplayName="相机视野(FOV)")
	float CameraFieldOfView{90.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State", Transient, DisplayName="右肩视角")
	uint8 bRightShoulder : 1 {true};

public:
	UAlsCameraComponent();

	virtual void PostLoad() override;

	virtual void OnRegister() override;

	virtual void RegisterComponentTickFunctions(bool bRegister) override;

	virtual void Activate(bool bReset) override;

	virtual void InitAnim(bool bForceReinitialize) override;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void CompleteParallelAnimationEvaluation(bool bDoPostAnimationEvaluation) override;

public:
	bool IsFieldOfViewOverriden() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Camera")
	void SetFieldOfViewOverriden(bool bNewFieldOfViewOverriden);

	float GetFieldOfViewOverride() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Camera")
	void SetFieldOfViewOverride(float NewFieldOfView);

	float GetPostProcessWeight() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Camera")
	void SetPostProcessWeight(float NewPostProcessWeight);

	bool IsRightShoulder() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|Camera")
	void SetRightShoulder(bool bNewRightShoulder);

	UFUNCTION(BlueprintPure, Category = "ALS|Camera", Meta = (ReturnDisplayName = "Camera Location"))
	FVector GetFirstPersonCameraLocation() const;

	UFUNCTION(BlueprintPure, Category = "ALS|Camera", Meta = (ReturnDisplayName = "Pivot Location"))
	FVector GetThirdPersonPivotLocation() const;

	UFUNCTION(BlueprintPure, Category = "ALS|Camera", Meta = (ReturnDisplayName = "Trace Start"))
	FVector GetThirdPersonTraceStartLocation() const;

	UFUNCTION(BlueprintPure, Category = "ALS|Camera")
	void GetViewInfo(FMinimalViewInfo& ViewInfo) const;

private:
	void TickCamera(float DeltaTime, bool bAllowLag = true);

	FRotator CalculateCameraRotation(const FRotator& CameraTargetRotation, float DeltaTime, bool bAllowLag) const;

	FVector CalculatePivotLagLocation(const FQuat& CameraYawRotation, float DeltaTime, bool bAllowLag) const;

	FVector CalculatePivotOffset() const;

	FVector CalculateCameraOffset() const;

	float CalculateFovOffset() const;

	FVector CalculateCameraTrace(const FVector& CameraTargetLocation, const FVector& PivotOffset,
	                             float DeltaTime, bool bAllowLag, float& NewTraceDistanceRatio) const;

	bool TryAdjustLocationBlockedByGeometry(FVector& Location, bool bDisplayDebugCameraTraces) const;

	// Debug

public:
	void DisplayDebug(const UCanvas* Canvas, const FDebugDisplayInfo& DisplayInfo, float& VerticalLocation) const;

private:
	static void DisplayDebugHeader(const UCanvas* Canvas, const FText& HeaderText, const FLinearColor& HeaderColor,
	                               float Scale, float HorizontalLocation, float& VerticalLocation);

	void DisplayDebugCurves(const UCanvas* Canvas, float Scale, float HorizontalLocation,
	                        float& VerticalLocation) const;

	void DisplayDebugShapes(const UCanvas* Canvas, float Scale, float HorizontalLocation,
	                        float& VerticalLocation) const;

	void DisplayDebugTraces(const UCanvas* Canvas, float Scale, float HorizontalLocation,
	                        float& VerticalLocation) const;
};

inline bool UAlsCameraComponent::IsFieldOfViewOverriden() const
{
	return bOverrideFieldOfView;
}

inline void UAlsCameraComponent::SetFieldOfViewOverriden(const bool bNewFieldOfViewOverriden)
{
	bOverrideFieldOfView = bNewFieldOfViewOverriden;
}

inline float UAlsCameraComponent::GetFieldOfViewOverride() const
{
	return FieldOfViewOverride;
}

inline void UAlsCameraComponent::SetFieldOfViewOverride(const float NewFieldOfView)
{
	FieldOfViewOverride = FMath::Clamp(NewFieldOfView, 5.0f, 175.0f);
}

inline float UAlsCameraComponent::GetPostProcessWeight() const
{
	return PostProcessWeight;
}

inline void UAlsCameraComponent::SetPostProcessWeight(const float NewPostProcessWeight)
{
	PostProcessWeight = UAlsMath::Clamp01(NewPostProcessWeight);
}

inline bool UAlsCameraComponent::IsRightShoulder() const
{
	return bRightShoulder;
}

inline void UAlsCameraComponent::SetRightShoulder(const bool bNewRightShoulder)
{
	bRightShoulder = bNewRightShoulder;
}
