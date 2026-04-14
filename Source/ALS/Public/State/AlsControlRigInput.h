#pragma once

#include "AlsControlRigInput.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsControlRigInput
{
	GENERATED_BODY()

	// TODO Replace bool with uint8 in future engine versions.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (DisplayName = "使用手 IK 骨", ToolTip = "是否在 Control Rig 中使用手部 IK 骨。"))
	bool bUseHandIkBones{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (DisplayName = "使用脚 IK 骨", ToolTip = "是否在 Control Rig 中使用脚部 IK 骨。"))
	bool bUseFootIkBones{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (DisplayName = "脚部变换有效", ToolTip = "当前脚部位置与旋转数据是否有效。"))
	bool bFootTransformsValid{false};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "前向速度混合量", ToolTip = "前向移动方向的速度混合权重。"))
	float VelocityBlendForwardAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "后向速度混合量", ToolTip = "后向移动方向的速度混合权重。"))
	float VelocityBlendBackwardAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (ClampMin = -180, ClampMax = 180, ForceUnits = "deg", DisplayName = "脊椎偏航角", ToolTip = "传递给 Control Rig 的脊椎偏航角。"))
	float SpineYawAngle{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "骨盆偏移量", ToolTip = "骨盆位置修正的混合权重。"))
	float PelvisOffsetAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (DisplayName = "左脚位置", ToolTip = "Control Rig 使用的左脚目标位置。"))
	FVector FootLeftLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (DisplayName = "左脚旋转", ToolTip = "Control Rig 使用的左脚目标旋转。"))
	FQuat FootLeftRotation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (DisplayName = "右脚位置", ToolTip = "Control Rig 使用的右脚目标位置。"))
	FVector FootRightLocation{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|控制绑定输入",
		Meta = (DisplayName = "右脚旋转", ToolTip = "Control Rig 使用的右脚目标旋转。"))
	FQuat FootRightRotation{ForceInit};
};
