#pragma once

#include "AlsLayeringState.generated.h"

USTRUCT(BlueprintType)
struct ALS_API FAlsLayeringState
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "头部混合量", ToolTip = "头部层的混合权重。"))
	float HeadBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "头部叠加混合量", ToolTip = "头部叠加层的混合权重。"))
	float HeadAdditiveBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "头部槽位混合量", ToolTip = "头部槽位层的混合权重。"))
	float HeadSlotBlendAmount{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "左臂混合量", ToolTip = "左臂层的混合权重。"))
	float ArmLeftBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "左臂叠加混合量", ToolTip = "左臂叠加层的混合权重。"))
	float ArmLeftAdditiveBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "左臂槽位混合量", ToolTip = "左臂槽位层的混合权重。"))
	float ArmLeftSlotBlendAmount{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "左臂局部空间混合量", ToolTip = "左臂局部空间混合权重。"))
	float ArmLeftLocalSpaceBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "左臂网格空间混合量", ToolTip = "左臂网格空间混合权重。"))
	float ArmLeftMeshSpaceBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "右臂混合量", ToolTip = "右臂层的混合权重。"))
	float ArmRightBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "右臂叠加混合量", ToolTip = "右臂叠加层的混合权重。"))
	float ArmRightAdditiveBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "右臂槽位混合量", ToolTip = "右臂槽位层的混合权重。"))
	float ArmRightSlotBlendAmount{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "右臂局部空间混合量", ToolTip = "右臂局部空间混合权重。"))
	float ArmRightLocalSpaceBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "右臂网格空间混合量", ToolTip = "右臂网格空间混合权重。"))
	float ArmRightMeshSpaceBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "左手混合量", ToolTip = "左手层的混合权重。"))
	float HandLeftBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "右手混合量", ToolTip = "右手层的混合权重。"))
	float HandRightBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "脊椎混合量", ToolTip = "脊椎层的混合权重。"))
	float SpineBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "脊椎叠加混合量", ToolTip = "脊椎叠加层的混合权重。"))
	float SpineAdditiveBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "脊椎槽位混合量", ToolTip = "脊椎槽位层的混合权重。"))
	float SpineSlotBlendAmount{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "骨盆混合量", ToolTip = "骨盆层的混合权重。"))
	float PelvisBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "骨盆槽位混合量", ToolTip = "骨盆槽位层的混合权重。"))
	float PelvisSlotBlendAmount{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "腿部混合量", ToolTip = "腿部层的混合权重。"))
	float LegsBlendAmount{0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|状态",
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "腿部槽位混合量", ToolTip = "腿部槽位层的混合权重。"))
	float LegsSlotBlendAmount{1.0f};
};
