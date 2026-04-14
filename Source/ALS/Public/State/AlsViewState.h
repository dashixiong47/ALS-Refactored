#pragma once

#include "AlsViewState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsViewNetworkSmoothingState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "已启用", ToolTip = "当前是否启用了视角网络平滑。"))
	uint8 bEnabled : 1 {false};

	// Used to track the time of the last server move.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "服务器时间", ToolTip = "最近一次服务器校正时的服务器时间。"))
	float ServerTime{0.0f};

	// Used to track client time as we try to match the server.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "客户端时间", ToolTip = "用于追赶服务器的客户端平滑时间。"))
	float ClientTime{0.0f};

	// Used for remembering how much time passed between server corrections.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "持续时间", ToolTip = "两次服务器校正之间的持续时间。"))
	float Duration{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "初始旋转", ToolTip = "网络平滑开始时的初始旋转。"))
	FRotator InitialRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "目标旋转", ToolTip = "网络平滑试图逼近的目标旋转。"))
	FRotator TargetRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "当前旋转", ToolTip = "网络平滑当前输出的旋转。"))
	FRotator CurrentRotation{ForceInit};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsViewState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "网络平滑状态", ToolTip = "视角网络平滑相关的运行时状态。"))
	FAlsViewNetworkSmoothingState NetworkSmoothing;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (DisplayName = "旋转", ToolTip = "当前平滑后的视角旋转。"))
	FRotator Rotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ForceUnits = "deg/s", DisplayName = "偏航速度", ToolTip = "当前视角偏航变化速度。"))
	float YawSpeed{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "上一帧偏航角", ToolTip = "上一帧记录的视角偏航角。"))
	float PreviousYawAngle{0.0f};
};
