// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AlsCharacter.h"
#include "GenericTeamAgentInterface.h"
#include "ALSBasePlayer.generated.h"

class UAlsCameraComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMontageNotifyNameOnly, FName, NotifyName);
UCLASS()
class ALSEXTRAS_API AALSBasePlayer : public AAlsCharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
protected:
	// UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Als Character Example")
	// TObjectPtr<UAlsCameraComponent> Camera;
public:
	// Sets default values for this character's properties
	AALSBasePlayer();
	UPROPERTY( BlueprintAssignable, Category = "ALS")
	FOnMontageNotifyNameOnly OnPlayMontageNotify;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FGenericTeamId TeamId;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// virtual void CalcCamera(float DeltaTime, FMinimalViewInfo& ViewInfo) override;
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamId; }
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void BindPlayMontageNotify();
	UFUNCTION(BlueprintCallable)
	void UnbindPlayMontageNotify();
	UFUNCTION()
	void PlayMontageNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);
	
	UFUNCTION(BlueprintCallable, Category = "BaseCharacter")
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
};
