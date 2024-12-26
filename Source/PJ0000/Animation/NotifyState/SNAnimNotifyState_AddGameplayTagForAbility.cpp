// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ0000/Animation/NotifyState/SNAnimNotifyState_AddGameplayTagForAbility.h"

#include "AbilitySystemComponent.h"
#include "SNDef.h"
#include "GameFramework/Character.h"

void USNAnimNotifyState_AddGameplayTagForAbility::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	ACharacter* Character(Cast<ACharacter>(MeshComp->GetOwner()));

	if (Character != nullptr)
	{
		UAbilitySystemComponent* AbilitySystemComponent = Cast<UAbilitySystemComponent>(Character->GetComponentByClass(UAbilitySystemComponent::StaticClass()));

		if (AbilitySystemComponent != nullptr)
		{
			AbilitySystemComponent->AddLooseGameplayTags(AbilityTags);
#if WITH_EDITORONLY_DATA
			if (bDebugDraw == true)
			{
				SNPLUGIN_LOG(TEXT("Add Ability %s."), *AbilityTags.ToString());	
			}
#endif
			
		}
	}
}

void USNAnimNotifyState_AddGameplayTagForAbility::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ACharacter* Character(Cast<ACharacter>(MeshComp->GetOwner()));

	if (Character != nullptr)
	{
		UAbilitySystemComponent* AbilitySystemComponent = Cast<UAbilitySystemComponent>(Character->GetComponentByClass(UAbilitySystemComponent::StaticClass()));

		if (AbilitySystemComponent != nullptr)
		{
			AbilitySystemComponent->RemoveLooseGameplayTags(AbilityTags);
#if WITH_EDITORONLY_DATA
			if (bDebugDraw == true)
			{
				SNPLUGIN_LOG(TEXT("Remove Ability %s."), *AbilityTags.ToString());
			}
#endif

				
		}
	}
}
