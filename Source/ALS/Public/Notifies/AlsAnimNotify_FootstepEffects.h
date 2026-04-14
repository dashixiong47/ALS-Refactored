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
	Left,
	Right,
};

UENUM(BlueprintType)
enum class EAlsFootstepSoundType : uint8
{
	Step,
	WalkRun,
	Land
};

UENUM(BlueprintType)
enum class EAlsFootstepSoundSpawnMode : uint8
{
	SpawnAtTraceHitLocation,
	SpawnAttachedToFootBone
};

UENUM(BlueprintType)
enum class EAlsFootstepDecalSpawnMode : uint8
{
	SpawnAtTraceHitLocation,
	SpawnAttachedToTraceHitComponent
};

UENUM(BlueprintType)
enum class EAlsFootstepParticleEffectSpawnMode : uint8
{
	SpawnAtTraceHitLocation,
	SpawnAttachedToFootBone
};

USTRUCT(BlueprintType)
struct ALS_API FAlsFootstepSoundSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚步音效设置",
		Meta = (DisplayName = "声音", ToolTip = "脚步触发时播放的声音资源。"))
	TSoftObjectPtr<USoundBase> Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚步音效设置",
		Meta = (DisplayName = "生成模式", ToolTip = "脚步声音的生成方式。"))
	EAlsFootstepSoundSpawnMode SpawnMode{EAlsFootstepSoundSpawnMode::SpawnAtTraceHitLocation};
};

USTRUCT(BlueprintType)
struct ALS_API FAlsFootstepDecalSettings
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (DisplayName = "贴花材质", ToolTip = "脚印生成时使用的贴花材质。"))
	TSoftObjectPtr<UMaterialInterface> DecalMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (DisplayName = "生成模式", ToolTip = "脚印贴花的生成方式。"))
	EAlsFootstepDecalSpawnMode SpawnMode{EAlsFootstepDecalSpawnMode::SpawnAttachedToTraceHitComponent};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (AllowPreserveRatio, DisplayName = "尺寸", ToolTip = "脚印贴花的尺寸。"))
	FVector3f Size{10.0f, 20.0f, 20.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "持续时间", ToolTip = "脚印贴花保留的总时长。"))
	float Duration{4.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (ClampMin = 0, ForceUnits = "s", DisplayName = "淡出时长", ToolTip = "脚印贴花淡出的时长。"))
	float FadeOutDuration{2.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (DisplayName = "位置偏移", ToolTip = "脚印生成时附加的位置偏移。"))
	FVector3f LocationOffset{0.0f, -10.0f, -1.75f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (DisplayName = "左脚旋转偏移", ToolTip = "左脚生成脚印时附加的旋转偏移。"))
	FRotator3f FootLeftRotationOffset{90.0f, 0.0f, -90.0f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置",
		Meta = (DisplayName = "右脚旋转偏移", ToolTip = "右脚生成脚印时附加的旋转偏移。"))
	FRotator3f FootRightRotationOffset{-90.0f, 0.0f, 90.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置", AdvancedDisplay,
		Meta = (DisplayName = "左脚旋转偏移四元数", ToolTip = "左脚旋转偏移对应的四元数缓存。"))
	FQuat4f FootLeftRotationOffsetQuaternion{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS|脚印设置", AdvancedDisplay,
		Meta = (DisplayName = "右脚旋转偏移四元数", ToolTip = "右脚旋转偏移对应的四元数缓存。"))
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|粒子设置",
		Meta = (DisplayName = "粒子系统", ToolTip = "脚步触发时生成的粒子系统。"))
	TSoftObjectPtr<UNiagaraSystem> ParticleSystem;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|粒子设置",
		Meta = (DisplayName = "生成模式", ToolTip = "脚步粒子系统的生成方式。"))
	EAlsFootstepParticleEffectSpawnMode SpawnMode{EAlsFootstepParticleEffectSpawnMode::SpawnAtTraceHitLocation};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|粒子设置",
		Meta = (DisplayName = "位置偏移", ToolTip = "脚步粒子生成时附加的位置偏移。"))
	FVector3f LocationOffset{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|粒子设置",
		Meta = (DisplayName = "左脚旋转偏移", ToolTip = "左脚粒子生成时附加的旋转偏移。"))
	FRotator3f FootLeftRotationOffset{ForceInit};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|粒子设置",
		Meta = (DisplayName = "右脚旋转偏移", ToolTip = "右脚粒子生成时附加的旋转偏移。"))
	FRotator3f FootRightRotationOffset{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS|粒子设置", AdvancedDisplay,
		Meta = (DisplayName = "左脚旋转偏移四元数", ToolTip = "左脚粒子旋转偏移对应的四元数缓存。"))
	FQuat4f FootLeftRotationOffsetQuaternion{ForceInit};

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "ALS|粒子设置", AdvancedDisplay,
		Meta = (DisplayName = "右脚旋转偏移四元数", ToolTip = "右脚粒子旋转偏移对应的四元数缓存。"))
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚步效果设置",
		Meta = (DisplayName = "声音设置", ToolTip = "脚步声音相关设置。"))
	FAlsFootstepSoundSettings Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚步效果设置",
		Meta = (DisplayName = "脚印设置", ToolTip = "脚步贴花相关设置。"))
	FAlsFootstepDecalSettings Decal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ALS|脚步效果设置",
		Meta = (DisplayName = "粒子设置", ToolTip = "脚步粒子相关设置。"))
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置",
		Meta = (DisplayName = "地表检测通道", ToolTip = "脚步地表检测使用的碰撞通道。"))
	TEnumAsByte<ECollisionChannel> SurfaceTraceChannel{ECC_Visibility};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置",
		Meta = (ClampMin = 0, ForceUnits = "cm", DisplayName = "地表检测距离", ToolTip = "脚步地表检测的最大距离。"))
	float SurfaceTraceDistance{50.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置", DisplayName = "左脚 Y 轴",
		Meta = (ToolTip = "左脚生成效果时使用的 Y 轴方向。"))
	FVector3f FootLeftYAxis{0.0f, 0.0f, 1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置", DisplayName = "左脚 Z 轴",
		Meta = (ToolTip = "左脚生成效果时使用的 Z 轴方向。"))
	FVector3f FootLeftZAxis{1.0f, 0.0f, 0.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置", DisplayName = "右脚 Y 轴",
		Meta = (ToolTip = "右脚生成效果时使用的 Y 轴方向。"))
	FVector3f FootRightYAxis{0.0f, 0.0f, 1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置", DisplayName = "右脚 Z 轴",
		Meta = (ToolTip = "右脚生成效果时使用的 Z 轴方向。"))
	FVector3f FootRightZAxis{-1.0f, 0.0f, 0.0f};

	// Prevents footstep decals from spawning if the angle between the foot's Z axis and the surface normal exceeds this value.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置",
		Meta = (ClampMin = 0, ClampMax = 90, ForceUnits = "deg", DisplayName = "脚印生成角度阈值",
		        ToolTip = "脚部 Z 轴与表面法线夹角超过该值时，不会生成脚印贴花。"))
	float DecalSpawnAngleThreshold{35.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置", AdvancedDisplay,
		Meta = (ClampMin = 0, ClampMax = 1, DisplayName = "脚印生成角度阈值余弦", ToolTip = "脚印生成角度阈值对应的余弦缓存。"))
	float DecalSpawnAngleThresholdCos{FMath::Cos(FMath::DegreesToRadians(35.0f))};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|脚步效果资源|设置",
		Meta = (ForceInlineRow, DisplayName = "效果映射表", ToolTip = "不同物理表面对应的脚步效果映射表。"))
	TMap<TEnumAsByte<EPhysicalSurface>, FAlsFootstepEffectSettings> Effects;

public:
#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& ChangedEvent) override;
#endif
};

UCLASS(DisplayName = "ALS 脚步效果动画通知",
	AutoExpandCategories = ("ALS|通知|声音", "ALS|通知|脚印", "ALS|通知|粒子"))
class ALS_API UAlsAnimNotify_FootstepEffects : public UAnimNotify
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (DisplayName = "脚步效果设置", ToolTip = "脚步效果通知使用的配置资源。"))
	TObjectPtr<UAlsFootstepEffectsSettings> FootstepEffectsSettings;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (DisplayName = "脚骨", ToolTip = "当前通知对应的脚骨。"))
	EAlsFootBone FootBone{EAlsFootBone::Left};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|设置",
		Meta = (DisplayName = "空中跳过效果", ToolTip = "启用后，角色在空中时不会触发脚步效果。"))
	uint8 bSkipEffectsWhenInAir : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|声音",
		Meta = (DisplayName = "生成声音", ToolTip = "是否生成脚步声音。"))
	uint8 bSpawnSound : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|声音",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "声音音量倍率", ToolTip = "脚步声音的音量倍率。"))
	float SoundVolumeMultiplier{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|声音",
		Meta = (ClampMin = 0, ForceUnits = "x", DisplayName = "声音音高倍率", ToolTip = "脚步声音的音高倍率。"))
	float SoundPitchMultiplier{1.0f};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|声音",
		Meta = (DisplayName = "声音类型", ToolTip = "当前脚步声音的类型。"))
	EAlsFootstepSoundType SoundType{EAlsFootstepSoundType::Step};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|声音",
		Meta = (DisplayName = "忽略脚步声音阻断曲线", ToolTip = "启用后，不会读取脚步声音阻断曲线来屏蔽声音。"))
	uint8 bIgnoreFootstepSoundBlockCurve : 1 {false};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|脚印",
		Meta = (DisplayName = "生成脚印", ToolTip = "是否生成脚印贴花。"))
	uint8 bSpawnDecal : 1 {true};

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ALS|通知|粒子",
		Meta = (DisplayName = "生成粒子", ToolTip = "是否生成脚步粒子效果。"))
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
	                const FHitResult& FootstepHit, const FVector& FootUpAxis) const;

	void SpawnParticleSystem(USkeletalMeshComponent* Mesh, const FAlsFootstepParticleSystemSettings& ParticleSystemSettings,
	                         const FVector& FootstepLocation, const FQuat& FootstepRotation) const;
};
