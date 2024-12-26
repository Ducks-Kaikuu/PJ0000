// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ0000/Character/Abilities/SNNormalAttackCombo01.h"
#include "GameplayAbilities/Public/Abilities/Tasks/AbilityTask_WaitGameplayTag.h"
#include "PlayMontageCallbackProxy.h"
#include "SNDef.h"
#include "GameFramework/Character.h"
#include "PJ0000/Character/Components/SNComboComponent.h"

void USNNormalAttackCombo01::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	CommitAbility(Handle, ActorInfo, ActivationInfo);

	ACharacter* Character(Cast<ACharacter>(ActorInfo->OwnerActor));

	USNComboComponent* ComboComponent = Character->FindComponentByClass<USNComboComponent>();

	if (ComboComponent != nullptr)
	{
		if (WaitTag.IsValid() && (Score > 0.0f))	
		{
			WaitGameplayTagAddedTask = UAbilityTask_WaitGameplayTagAdded::WaitGameplayTagAdd(this, WaitTag, nullptr, true);	

			WaitGameplayTagAddedTask->AbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
			
			WaitGameplayTagAddedTask->Added.AddDynamic(this, &USNNormalAttackCombo01::WaitGameplayTagAdded);

			SNPLUGIN_LOG(TEXT("Combo.Wait - %s - %s"), *GetName(), *WaitTag.ToString());

			ComboComponent->AddAbilityTask(WaitGameplayTagAddedTask);
			
			return;
		}

		//Score = 0.0f;
		
		PlayMontageProxy = PerformMotionMatching(Character);
		
	}

	SNPLUGIN_LOG(TEXT("Combo.Input : Score(%f)"), Score);
}

void USNNormalAttackCombo01::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	USNComboComponent* AbilitySystemComponent = Cast<USNComboComponent>(GetAbilitySystemComponentFromActorInfo());

	if (AbilitySystemComponent != nullptr)
	{
		AbilitySystemComponent->ResetAbilityGameplayTags();
	}
}

UPlayMontageCallbackProxy* USNNormalAttackCombo01::PerformMotionMatching(ACharacter* Character)
{
	USNComboComponent* ComboComponent = Character->FindComponentByClass<USNComboComponent>();
	
	if (ComboComponent != nullptr)
	{
		ComboComponent->SetComboScore(Score);

		//PlayMontageProxy = ComboComponent->PerformMotionMatching(Character);

		Score += 1.0f;
		
		PlayMontageProxy->OnCompleted.AddDynamic(this, &USNNormalAttackCombo01::EndPlayMontag);
		//PlayMontageProxy->OnInterrupted.AddDynamic(this, &USNNormalAttackCombo01::EndPlayMontag);
		//PlayMontageProxy->OnBlendOut.AddDynamic(this, &USNNormalAttackCombo01::EndPlayMontag);
	}

	return PlayMontageProxy;
}

void USNNormalAttackCombo01::WaitGameplayTagAdded()
{
	ACharacter* Character(Cast<ACharacter>(GetActorInfo().OwnerActor));

	USNComboComponent* ComboComponent = Character->FindComponentByClass<USNComboComponent>();

	if (ComboComponent != nullptr)
	{
		PlayMontageProxy = PerformMotionMatching(Character);
		
		ComboComponent->RemoveAbilityTask(WaitGameplayTagAddedTask);
	}

	WaitGameplayTagAddedTask = nullptr;
}

void USNNormalAttackCombo01::EndPlayMontag(FName NotifyName)
{
	K2_EndAbility();

	Score = 0.0f;
}
