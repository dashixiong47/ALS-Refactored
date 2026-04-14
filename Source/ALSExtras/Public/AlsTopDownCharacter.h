#pragma once

#include "AlsCharacter.h"

#include "AlsTopDownCharacter.generated.h"

class UAlsTopDownInputConfig;
class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum class EAlsTopDownCameraRecenteringMode : uint8
{
	Disabled UMETA(DisplayName = "关闭"),
	Smooth UMETA(DisplayName = "缓慢居中"),
	Fast UMETA(DisplayName = "快速居中")
};

UCLASS(Blueprintable, Meta = (DisplayName = "ALS 俯视角角色", ToolTip = "基于 ALS 的俯视角角色基类，负责俯视角相机、移动与 ALS 朝向应用。"),
	PrioritizeCategories = ("ALS|俯视角", "ALS|俯视角|相机跟随", "ALS|俯视角|摄像机", "ALS|俯视角|输入", "ALS|俯视角|视角", "ALS|俯视角|瞄准", "ALS|俯视角|组件"),
	AutoExpandCategories = ("ALS|俯视角", "ALS|俯视角|摄像机"))
class ALSEXTRAS_API AAlsTopDownCharacter : public AAlsCharacter
{
	GENERATED_BODY()

public:
	AAlsTopDownCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& ViewInfo) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|瞄准",
		Meta = (DisplayName = "默认保持瞄准", ToolTip = "启用后角色会默认保持 ALS 的瞄准旋转模式，让上半身先跟随视角，超限后再带动下半身。"))
	bool bDefaultToAimingRotation{true};

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ALS|俯视角|组件",
		Meta = (DisplayName = "弹簧臂", ToolTip = "俯视角摄像机使用的弹簧臂组件。"))
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ALS|俯视角|组件",
		Meta = (DisplayName = "摄像机", ToolTip = "俯视角摄像机组件。"))
	TObjectPtr<UCameraComponent> Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "启用屏幕死区跟随", ToolTip = "启用后角色在屏幕死区内移动时相机保持不动，超出后再追随。"))
	bool bEnableScreenDeadZoneFollow{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (ClampMin = "0.05", ClampMax = "1.0", DisplayName = "死区宽度占比", ToolTip = "屏幕死区宽度占整个视口宽度的比例。"))
	float DeadZoneWidthRatio{0.35f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (ClampMin = "0.05", ClampMax = "1.0", DisplayName = "死区高度占比", ToolTip = "屏幕死区高度占整个视口高度的比例。"))
	float DeadZoneHeightRatio{0.28f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (ClampMin = "0.0", DisplayName = "超出后跟随速度", ToolTip = "角色超出死区时，相机锚点追向死区边缘的插值速度。"))
	float DeadZoneFollowInterpSpeed{8.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "回中模式", ToolTip = "角色重新稳定后，相机是否以及如何自动回到角色中心。"))
	EAlsTopDownCameraRecenteringMode RecenteringMode{EAlsTopDownCameraRecenteringMode::Disabled};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (ClampMin = "0.0", DisplayName = "回中延迟时间", ToolTip = "角色持续停留在死区内达到该时长后，才开始自动回中。", ForceUnits = "s"))
	float RecenteringDelay{0.75f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (ClampMin = "0.0", DisplayName = "缓慢居中速度", ToolTip = "回中模式为“缓慢居中”时，相机锚点回到角色中心的插值速度。"))
	float SmoothRecenteringInterpSpeed{2.5f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (ClampMin = "0.0", DisplayName = "快速居中速度", ToolTip = "回中模式为“快速居中”时，相机锚点回到角色中心的插值速度。"))
	float FastRecenteringInterpSpeed{6.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "移动时禁止回中", ToolTip = "启用后角色仍在明显移动时不会启动自动回中计时。"))
	bool bDisableRecenteringWhileMoving{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (ClampMin = "0.0", DisplayName = "回中移动阈值", ToolTip = "低于该平面速度时，角色才会被视为进入可回中状态。", ForceUnits = "cm/s"))
	float RecenteringMovementThreshold{5.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (ClampMin = "0.0", DisplayName = "最小朝向变化阈值", ToolTip = "只有当鼠标目标朝向变化超过该阈值时才会刷新 ALS TopDownFacingYaw。", ForceUnits = "deg"))
	float FacingYawEpsilon{0.25f};

	UPROPERTY(Replicated, VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|网络",
		Meta = (DisplayName = "复制的鼠标瞄准点", ToolTip = "从客户端复制到服务端和其他客户端的鼠标瞄准世界坐标。"))
	FVector_NetQuantize ReplicatedCursorAimPoint;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|摄像机",
		Meta = (ClampMin = "0.0", DisplayName = "最小缩放距离", ToolTip = "俯视角摄像机允许的最小弹簧臂长度。", ForceUnits = "cm"))
	float ZoomMin{600.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|摄像机",
		Meta = (ClampMin = "0.0", DisplayName = "最大缩放距离", ToolTip = "俯视角摄像机允许的最大弹簧臂长度。", ForceUnits = "cm"))
	float ZoomMax{2500.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|摄像机",
		Meta = (ClampMin = "0.0", DisplayName = "缩放步长", ToolTip = "每次缩放输入会改变的弹簧臂长度。", ForceUnits = "cm"))
	float ZoomStep{200.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|摄像机",
		Meta = (ClampMin = "0.0", DisplayName = "缩放插值速度", ToolTip = "摄像机缩放的平滑插值速度。"))
	float ZoomInterpSpeed{10.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|摄像机",
		Meta = (DisplayName = "默认镜头俯仰", ToolTip = "弹簧臂默认俯仰角度。", ForceUnits = "deg"))
	float CameraPitch{-60.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|摄像机",
		Meta = (DisplayName = "默认镜头偏航", ToolTip = "弹簧臂默认偏航角度。", ForceUnits = "deg"))
	float CameraYaw{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "上次目标朝向", ToolTip = "最近一次用于驱动 ALS TopDownFacing 的目标偏航角。", ForceUnits = "deg"))
	float CachedFacingYaw{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "当前相机锚点", ToolTip = "当前俯视角相机跟随锚点的世界位置。"))
	FVector CameraAnchorLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "目标相机锚点", ToolTip = "当前俯视角相机希望追到的目标锚点位置。"))
	FVector CameraAnchorTargetLocation{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "回中计时", ToolTip = "角色稳定处于死区内后累计的回中等待时间。", ForceUnits = "s"))
	float CameraRecenteringTimer{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "正在回中", ToolTip = "当前是否正在执行自动回中。"))
	bool bIsCameraRecentering{false};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|相机跟随",
		Meta = (DisplayName = "超出死区", ToolTip = "当前角色投影是否超出屏幕死区。"))
	bool bIsOutsideCameraDeadZone{false};

	float TargetZoom{1500.0f};
	bool bCameraAnchorInitialized{false};

public:
	UFUNCTION(BlueprintCallable, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "应用俯视角移动输入", ToolTip = "将二维输入按俯视角摄像机方向转换成角色移动。"))
	void ApplyTopDownMoveInput(FVector2D InputValue);

	UFUNCTION(BlueprintCallable, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "应用缩放输入", ToolTip = "根据输入值调整俯视角摄像机缩放。"))
	void ApplyTopDownZoomInput(float InputValue);

	UFUNCTION(BlueprintCallable, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "按世界坐标计算目标偏航", ToolTip = "根据目标世界坐标计算俯视角瞄准偏航，不会直接转动角色。"))
	float CalculateTopDownAimYaw(const FVector& WorldTarget) const;

	UFUNCTION(Server, Unreliable)
	void ServerSetCursorAimPoint(FVector_NetQuantize CursorPoint);

private:
	void UpdateCameraAnchor(float DeltaTime);
	void UpdateCameraZoom(float DeltaTime);
	void ApplyCameraAnchorTransform() const;
	bool ResolveDeadZoneState(float DeltaTime, FVector& OutDesiredAnchor, bool& bOutShouldRecenter);
	bool DeprojectScreenPositionToGround(const FVector2D& ScreenPosition, const FPlane& GroundPlane, FVector& OutWorldPoint) const;
	void ApplyReplicatedCursorAim();
};
