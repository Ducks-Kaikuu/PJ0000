// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "SNNormalAttackCombo01.generated.h"

class UAbilityTask_WaitGameplayTagAdded;
class UPlayMontageCallbackProxy;
/**
 * 
 */
UCLASS()
class PJ0000_API USNNormalAttackCombo01 : public UGameplayAbility
{
	GENERATED_BODY()

	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
private:

	UPlayMontageCallbackProxy* PerformMotionMatching(ACharacter* Character);
	
	UPROPERTY(EditAnywhere, Category = "Combo")
	FGameplayTagContainer NextComboTag;

	UPROPERTY(EditAnywhere, Category = "Combo")
	FGameplayTag WaitTag = FGameplayTag();
	
	
	

	UPROPERTY(EditAnywhere, Category = "Combo")
	float Score = -1.0f;
	
	UFUNCTION()
	void EndPlayMontag(FName NotifyName);
	
	UFUNCTION()
	void WaitGameplayTagAdded();
	
	UPROPERTY()
	UPlayMontageCallbackProxy* PlayMontageProxy = nullptr;

	UPROPERTY()
	UAbilityTask_WaitGameplayTagAdded* WaitGameplayTagAddedTask = nullptr;
};

