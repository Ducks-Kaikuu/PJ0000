// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "MotionMatching/Character/SNMotionMatchingPlayerBase.h"
#include "PJCharacter.generated.h"

class UGameplayAbility;
/**
 * 
 */
UCLASS()
class PJ0000_API APJCharacter : public ASNMotionMatchingPlayerBase, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

private:

	UPROPERTY()
	TArray<TObjectPtr<UGameplayAbility>> Abilities;
	
	UPROPERTY(EditAnywhere, Category = "Ability")
	TArray<TSoftClassPtr<UGameplayAbility>> AbilityList;
};
