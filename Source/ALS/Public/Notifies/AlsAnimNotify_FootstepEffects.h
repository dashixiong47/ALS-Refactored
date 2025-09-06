#pragma once

#include "Animation/AnimNotifies/AnimNotify.h"
#include "Engine/DataAsset.h"
#include "Engine/EngineTypes.h"
#include "AlsAnimNotify_FootstepEffects.generated.h"

enum EPhysicalSurface : int;
struct FHitResult;
class USoundBase;
class UMaterialInterface;
class UNiagaraSystem;

UENUM(BlueprintType)
enum class EAlsFootBone : uint8
{
	Left UMETA(DisplayName = "左脚"),
	Right UMETA(DisplayName = "右脚")
};

UENUM(BlueprintType)
enum class EAlsFootstepSoundType : uint8
{
	Step UMETA(DisplayName = "踩踏"),
	WalkRun UMETA(DisplayName = "走/跑"),
	Land UMETA(DisplayName = "落地")
};

UENUM(BlueprintType)
enum class EAlsFootstepSoundSpawnMode : uint8
{
	SpawnAtTraceHitLocation UMETA(DisplayName = "在射线命中位置生成"),
	SpawnAttachedToFootBone UMETA(DisplayName = "附着到脚骨生成")
};

UENUM(BlueprintType)
enum class EAlsFootstepDecalSpawnMode : uint8
{
	SpawnAtTraceHitLocation UMETA(DisplayName = "在射线命中位置生成"),
	SpawnAttachedToTraceHitComponent UMETA(DisplayName = "附着到命中组件生成")
};

UENUM(BlueprintType)
enum class EAlsFootstepParticleEffectSpawnMode : uint8
{
	SpawnAtTraceHitLocation UMETA(DisplayName = "在射线命中位置生成"),
	SpawnAttachedToFootBone UMETA(DisplayName = "附着到脚骨生成")
};

USTRUCT(BlueprintType)
struct ALS_API FAlsFootstepSoundSettings
{
	GENERATED_BODY()

public:
	// 脚步音效资源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="脚步音效")
	TSoftObjectPtr<USoundBase> Sound;

	// 音效生成方式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="音效生成方式")
	EAlsFootstepSoundSpawnMode SpawnMode{EAlsFootstepSoundSpawnMode::SpawnAtTraceHitLocation};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsFootstepDecalSettings
{
	GENERATED_BODY()

public:
	// 脚印贴花材质
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="脚印贴花材质")
	TSoftObjectPtr<UMaterialInterface> DecalMaterial;

	// 贴花生成方式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="贴花生成方式")
	EAlsFootstepDecalSpawnMode SpawnMode{EAlsFootstepDecalSpawnMode::SpawnAttachedToTraceHitComponent};

	// 贴花尺寸
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="贴花尺寸", Meta = (AllowPreserveRatio))
	FVector3f Size{10.0f, 20.0f, 20.0f};

	// 持续时间 (秒)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="持续时间",
		Meta = (ClampMin = 0, ForceUnits = "s"))
	float Duration{4.0f};

	// 渐隐时间 (秒)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="渐隐时间",
		Meta = (ClampMin = 0, ForceUnits = "s"))
	float FadeOutDuration{2.0f};

	// 位置偏移
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="位置偏移")
	FVector3f LocationOffset{0.0f, -10.0f, -1.75f};

	// 左脚旋转偏移
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="左脚旋转偏移")
	FRotator3f FootLeftRotationOffset{90.0f, 0.0f, -90.0f};

	// 右脚旋转偏移
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="右脚旋转偏移")
	FRotator3f FootRightRotationOffset{-90.0f, 0.0f, 90.0f};

	// 左脚旋转四元数 (仅显示)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, DisplayName="左脚旋转四元数")
	FQuat4f FootLeftRotationOffsetQuaternion{ForceInit};

	// 右脚旋转四元数 (仅显示)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, DisplayName="右脚旋转四元数")
	FQuat4f FootRightRotationOffsetQuaternion{ForceInit};

public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};

USTRUCT(BlueprintType)
struct ALS_API FAlsFootstepParticleSystemSettings
{
	GENERATED_BODY()

public:
	// 粒子特效资源
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="粒子特效")
	TSoftObjectPtr<UNiagaraSystem> ParticleSystem;

	// 粒子生成方式
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="粒子生成方式")
	EAlsFootstepParticleEffectSpawnMode SpawnMode{EAlsFootstepParticleEffectSpawnMode::SpawnAtTraceHitLocation};

	// 位置偏移
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="位置偏移")
	FVector3f LocationOffset{ForceInit};

	// 左脚旋转偏移
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="左脚旋转偏移")
	FRotator3f FootLeftRotationOffset{ForceInit};

	// 右脚旋转偏移
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="右脚旋转偏移")
	FRotator3f FootRightRotationOffset{ForceInit};

	// 左脚旋转四元数 (仅显示)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, DisplayName="左脚旋转四元数")
	FQuat4f FootLeftRotationOffsetQuaternion{ForceInit};

	// 右脚旋转四元数 (仅显示)
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS", AdvancedDisplay, DisplayName="右脚旋转四元数")
	FQuat4f FootRightRotationOffsetQuaternion{ForceInit};

public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};

USTRUCT(BlueprintType)
struct ALS_API FAlsFootstepEffectSettings
{
	GENERATED_BODY()

public:
	// 脚步音效设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="脚步音效设置")
	FAlsFootstepSoundSettings Sound;

	// 脚步贴花设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="脚步贴花设置")
	FAlsFootstepDecalSettings Decal;

	// 脚步粒子特效设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS", DisplayName="脚步粒子特效设置")
	FAlsFootstepParticleSystemSettings ParticleSystem;

public:
#if WITH_EDITOR
	void PostEditChangeProperty(const FPropertyChangedEvent& ChangedEvent);
#endif
};

UCLASS(Blueprintable, BlueprintType)
class ALS_API UAlsFootstepEffectsSettings : public UDataAsset
{
	GENERATED_BODY()

public:
	// 表面检测通道
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="表面检测通道")
	TEnumAsByte<ECollisionChannel> SurfaceTraceChannel{ECC_Visibility};

	// 表面检测距离
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="表面检测距离",
		Meta = (ClampMin = 0, ForceUnits = "cm"))
	float SurfaceTraceDistance{50.0f};

	// 左脚 Y 轴
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="左脚 Y 轴")
	FVector3f FootLeftYAxis{0.0f, 0.0f, 1.0f};

	// 左脚 Z 轴
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="左脚 Z 轴")
	FVector3f FootLeftZAxis{1.0f, 0.0f, 0.0f};

	// 右脚 Y 轴
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="右脚 Y 轴")
	FVector3f FootRightYAxis{0.0f, 0.0f, 1.0f};

	// 右脚 Z 轴
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="右脚 Z 轴")
	FVector3f FootRightZAxis{-1.0f, 0.0f, 0.0f};

	// 阈值角度，超过则不生成脚步贴花
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings",
		DisplayName="贴花生成角度阈值", Meta = (ClampMin = 0, ClampMax = 90, ForceUnits = "deg"))
	float DecalSpawnAngleThreshold{35.0f};

	// 角度阈值余弦（仅显示）
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Settings", AdvancedDisplay,
		DisplayName="贴花生成角度阈值余弦", Meta = (ClampMin = 0, ClampMax = 1))
	float DecalSpawnAngleThresholdCos{FMath::Cos(FMath::DegreesToRadians(35.0f))};

	// 不同物理表面对应的脚步效果
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings",
		DisplayName="表面脚步效果映射", Meta = (ForceInlineRow))
	TMap<TEnumAsByte<EPhysicalSurface>, FAlsFootstepEffectSettings> Effects;

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
};


UCLASS(DisplayName = "ALS 脚步效果动画通知",
	AutoExpandCategories = ("Settings|Sound", "Settings|Decal", "Settings|Particle System"))
class ALS_API UAlsAnimNotify_FootstepEffects : public UAnimNotify
{
	GENERATED_BODY()

protected:
	// 脚步效果配置
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="脚步效果配置")
	TObjectPtr<UAlsFootstepEffectsSettings> FootstepEffectsSettings;

	// 脚（左 / 右）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="脚")
	EAlsFootBone FootBone{EAlsFootBone::Left};

	// 是否在空中时跳过效果
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings", DisplayName="空中时跳过效果")
	uint8 bSkipEffectsWhenInAir : 1 {false};

	// 是否生成脚步音效
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", DisplayName="生成脚步音效")
	uint8 bSpawnSound : 1 {true};

	// 音量倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound",
		DisplayName="音量倍率", Meta = (ClampMin = 0, ForceUnits = "x"))
	float SoundVolumeMultiplier{1.0f};

	// 音调倍率
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound",
		DisplayName="音调倍率", Meta = (ClampMin = 0, ForceUnits = "x"))
	float SoundPitchMultiplier{1.0f};

	// 音效类型（踩踏 / 行走跑步 / 落地）
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", DisplayName="音效类型")
	EAlsFootstepSoundType SoundType{EAlsFootstepSoundType::Step};

	// 是否忽略动画曲线里的“阻止脚步音效”
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Sound", DisplayName="忽略音效阻止曲线")
	uint8 bIgnoreFootstepSoundBlockCurve : 1 {false};

	// 是否生成脚步贴花
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Decal", DisplayName="生成脚步贴花")
	uint8 bSpawnDecal : 1 {true};

	// 是否生成脚步粒子特效
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings|Particle System", DisplayName="生成脚步粒子特效")
	uint8 bSpawnParticleSystem : 1 {true};

public:
	virtual FString GetNotifyName_Implementation() const override;

#if WITH_EDITOR
	virtual void OnAnimNotifyCreatedInEditor(FAnimNotifyEvent& NotifyEvent) override;
#endif

	virtual void Notify(USkeletalMeshComponent* Mesh, UAnimSequenceBase* Sequence,
	                    const FAnimNotifyEventReference& NotifyEventReference) override;

private:
	void SpawnSound(USkeletalMeshComponent* Mesh, const FAlsFootstepSoundSettings& SoundSettings,
	                const FVector& FootstepLocation, const FQuat& FootstepRotation) const;

	void SpawnDecal(USkeletalMeshComponent* Mesh, const FAlsFootstepDecalSettings& DecalSettings,
	                const FVector& FootstepLocation, const FQuat& FootstepRotation,
	                const FHitResult& FootstepHit, const FVector& FootZAxis) const;

	void SpawnParticleSystem(USkeletalMeshComponent* Mesh,
	                         const FAlsFootstepParticleSystemSettings& ParticleSystemSettings,
	                         const FVector& FootstepLocation, const FQuat& FootstepRotation) const;
};
