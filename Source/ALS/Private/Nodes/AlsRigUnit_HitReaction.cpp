#include "Nodes/AlsRigUnit_HitReaction.h"
#include UE_INLINE_GENERATED_CPP_BY_NAME(AlsRigUnit_HitReaction)
FAlsRigUnit_SpineHitReaction_Execute()
{
	DECLARE_SCOPE_HIERARCHICAL_COUNTER_RIGUNIT()

	auto* Hierarchy = ExecuteContext.Hierarchy;
	if (!IsValid(Hierarchy))
		return;

	if (CachedSpine.Num() != SpineChain.Num())
		CachedSpine.SetNum(SpineChain.Num());

	if (HitDirection.IsNearlyZero() || HitStrength <= KINDA_SMALL_NUMBER || HitAlpha <= 0.0f)
		return;

	// ====== 改进：直接用骨骼 Transform 构建坐标系 ======
	if (SpineChain.Num() == 0 || !CachedSpine[0].UpdateCache(SpineChain[0], Hierarchy))
		return;

	const FTransform RootTransform = Hierarchy->GetGlobalTransform(CachedSpine[0]);
	const FQuat BoneQuat = RootTransform.GetRotation();
	const FRotator BoneRot = BoneQuat.Rotator();
	const FMatrix BoneBasis = FRotationMatrix(BoneRot);

	const FVector Forward = BoneBasis.GetUnitAxis(EAxis::X); // 骨骼前向
	const FVector Right   = BoneBasis.GetUnitAxis(EAxis::Y); // 骨骼右向
	const FVector Up      = BoneBasis.GetUnitAxis(EAxis::Z); // 骨骼上向

	// 确保受击方向指向角色
	const FVector Dir = -HitDirection.GetSafeNormal();

	for (int32 i = 0; i < SpineChain.Num(); i++)
	{
		if (!CachedSpine[i].UpdateCache(SpineChain[i], Hierarchy))
			continue;

		FTransform BoneTransform = Hierarchy->GetGlobalTransform(CachedSpine[i]);

		// 权重衰减
		const float Weight = 1.0f - (float(i) / (float)SpineChain.Num());
		const float Angle = HitStrength * Weight * HitAlpha;

		// 投影到局部骨骼坐标系
		const FVector LocalDir = BoneBasis.InverseTransformVector(Dir);

		// ====== 调试输出 ======
		UE_LOG(LogTemp, Warning, TEXT("Spine[%d] LocalDir: X=%.3f, Y=%.3f, Z=%.3f"),
			i, LocalDir.X, LocalDir.Y, LocalDir.Z);

		// 自动选择旋转轴
		FVector Axis = FVector::ZeroVector;
		float FinalAngle = Angle;

		const float AbsX = FMath::Abs(LocalDir.X);
		const float AbsY = FMath::Abs(LocalDir.Y);
		const float AbsZ = FMath::Abs(LocalDir.Z);

		if (AbsX >= AbsY && AbsX >= AbsZ)
		{
			Axis = Right;          // 前后 -> Pitch
			if (LocalDir.X < 0) FinalAngle = -Angle;
		}
		else if (AbsY >= AbsX && AbsY >= AbsZ)
		{
			Axis = Up;             // 左右 -> Yaw
			if (LocalDir.Y < 0) FinalAngle = -Angle;
		}
		else
		{
			Axis = Forward;        // 上下 -> Roll
			if (LocalDir.Z < 0) FinalAngle = -Angle;
		}

		const FQuat HitQuat = FQuat(Axis, FMath::DegreesToRadians(FinalAngle));
		const FQuat NewQuat = HitQuat * BoneTransform.GetRotation();

		BoneTransform.SetRotation(NewQuat);
		Hierarchy->SetGlobalTransform(CachedSpine[i], BoneTransform);
	}
}