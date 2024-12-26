// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ0000/Character/PJCharacter.h"

#include "AbilitySystemComponent.h"

UAbilitySystemComponent* APJCharacter::GetAbilitySystemComponent() const
{
	UAbilitySystemComponent* AbilitySystemComponent = Cast<UAbilitySystemComponent>(GetComponentByClass(UAbilitySystemComponent::StaticClass()));

	return AbilitySystemComponent;
}


