#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "AlsTopDownPlayerController.generated.h"

class UAlsTopDownInputConfig;
struct FInputActionValue;

UENUM(BlueprintType)
enum class EAlsTopDownAimPointMode : uint8
{
	GroundPlane UMETA(DisplayName = "固定地面平面"),
	CursorHit UMETA(DisplayName = "鼠标射线命中")
};

UCLASS(Blueprintable, Meta = (DisplayName = "ALS 俯视角控制器", ToolTip = "负责俯视角本地鼠标逻辑、输入映射上下文与默认输入绑定的 ALS 控制器。"),
	PrioritizeCategories = ("ALS|俯视角", "ALS|俯视角|输入", "ALS|俯视角|视角"),
	AutoExpandCategories = ("ALS|俯视角", "ALS|俯视角|输入", "ALS|俯视角|视角"))
class ALSEXTRAS_API AAlsTopDownPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AAlsTopDownPlayerController();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "输入配置", ToolTip = "当前控制器用于默认绑定和映射上下文注入的输入配置。", DisplayThumbnail = false))
	TObjectPtr<UAlsTopDownInputConfig> InputConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "自动管理输入映射", ToolTip = "启用后会在本地玩家控制器开始和结束时自动添加/移除映射上下文。"))
	bool bAutoManageInputMappingContext{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "持续跟随鼠标朝向", ToolTip = "启用后会在本地玩家 Tick 中持续读取鼠标命中点，并将朝向同步给当前角色。"))
	bool bUpdateFacingFromCursorEveryTick{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "仅鼠标移动时更新瞄准", ToolTip = "启用后只有鼠标屏幕位置真正发生变化时才会更新控制器瞄准，避免角色移动和相机变化引起的无效网络旋转同步。"))
	bool bOnlyUpdateAimWhenCursorMoves{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (ClampMin = "0.0", DisplayName = "鼠标移动阈值", ToolTip = "只有当鼠标在屏幕上的位移超过该阈值时，才会重新计算并同步瞄准方向。", ForceUnits = "px"))
	float CursorScreenMoveThreshold{1.5f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "瞄准取点模式", ToolTip = "控制俯视角瞄准是使用固定地面平面，还是使用鼠标射线实际命中点。"))
	EAlsTopDownAimPointMode AimPointMode{EAlsTopDownAimPointMode::GroundPlane};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "鼠标射线通道", ToolTip = "用于命中地面的鼠标射线通道。"))
	TEnumAsByte<ECollisionChannel> CursorTraceChannel{ECC_Visibility};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "启用命中点平滑", ToolTip = "启用后会先平滑鼠标对应的世界点，再更新控制器瞄准方向。"))
	bool bSmoothAimPoint{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (ClampMin = "0.0", DisplayName = "命中点平滑速度", ToolTip = "鼠标世界点平滑到目标位置时使用的插值速度。"))
	float AimPointSmoothingSpeed{18.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "启用瞄准限频", ToolTip = "启用后会限制控制器真正写入瞄准旋转的最小时间间隔。"))
	bool bLimitAimUpdateRate{true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (ClampMin = "0.0", DisplayName = "瞄准最小更新时间间隔", ToolTip = "两次真正写入控制器瞄准旋转之间的最小时间间隔。", ForceUnits = "s"))
	float MinAimUpdateInterval{0.033f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (ClampMin = "0.0", DisplayName = "瞄准偏航更新阈值", ToolTip = "只有当瞄准偏航变化超过该阈值时，才真正写入控制器旋转。", ForceUnits = "deg"))
	float AimYawUpdateThreshold{1.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "鼠标命中点", ToolTip = "最近一次鼠标命中的世界坐标。"))
	FVector CursorWorldPoint{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "上次处理鼠标位置", ToolTip = "最近一次真正参与瞄准计算的鼠标屏幕位置。", ForceUnits = "px"))
	FVector2D LastProcessedCursorScreenPosition{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "平滑后瞄准点", ToolTip = "经过平滑后的俯视角瞄准世界坐标。"))
	FVector SmoothedAimWorldPoint{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "上次应用偏航", ToolTip = "最近一次真正写入控制器旋转的俯视角偏航。", ForceUnits = "deg"))
	float LastAppliedAimYaw{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "上次更新时间", ToolTip = "最近一次真正写入控制器旋转的时间。", ForceUnits = "s"))
	float LastAimUpdateTime{0.0f};

	bool bHasSmoothedAimPoint{false};
	bool bHasProcessedCursorScreenPosition{false};

public:
	UFUNCTION(BlueprintPure, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "获取输入配置", ToolTip = "返回当前控制器使用的 ALS 俯视角输入配置。"))
	UAlsTopDownInputConfig* GetTopDownInputConfig() const;

	UFUNCTION(BlueprintCallable, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "绑定默认 TopDown 输入", ToolTip = "按输入配置中的动作把默认移动和缩放绑定到当前控制器输入组件。"))
	void BindDefaultTopDownInput();

	UFUNCTION(BlueprintCallable, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "按鼠标刷新瞄准视角", ToolTip = "读取鼠标命中点并更新控制器视角，让 ALS 走原生 Aiming 约束。", ReturnDisplayName = "成功"))
	bool UpdateAimFromCursor();

	UFUNCTION(BlueprintCallable, Category = "ALS|俯视角|视角",
		Meta = (DisplayName = "获取鼠标世界点", ToolTip = "计算当前鼠标对应的地面世界坐标。", ReturnDisplayName = "成功"))
	bool QueryCursorWorldPoint(FVector& OutWorldPoint) const;

protected:
	UFUNCTION(BlueprintImplementableEvent, Category = "ALS|俯视角|输入",
		Meta = (DisplayName = "配置 TopDown 输入", ToolTip = "控制器输入组件创建后调用；蓝图或 AngelScript 可在此调用默认绑定器，或追加自定义输入绑定。"))
	void SetupTopDownInput();

private:
	void ApplyInputMappingContext(bool bAddMappingContext);
	void HandleMoveAction(const FInputActionValue& ActionValue);
	void HandleZoomAction(const FInputActionValue& ActionValue);
	class AAlsTopDownCharacter* ResolveTopDownCharacter() const;
	bool ApplyAimYaw(float NewYaw);
	bool QueryGroundPlaneAimPoint(FVector& OutWorldPoint) const;
};
