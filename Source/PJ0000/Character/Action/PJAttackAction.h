// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SNActionBase.h"
#include "PJAttackAction.generated.h"

class UPlayMontageCallbackProxy;
/**
 * 
 */
UCLASS()
class PJ0000_API UPJAttackAction : public USNActionBase
{
	GENERATED_BODY()

public:
	virtual void ExecAction(const FInputActionValue& InputActionValue) override;

private:
	UPROPERTY(EditAnywhere, Category="SN|Attack")
	FGameplayTag AdvancedInput = FGameplayTag();

	UPROPERTY(EditAnywhere, Category="SN|Attack")
	FGameplayTag Branch = FGameplayTag();
	
	UPROPERTY(EditAnywhere, Category="SN|Attack")
	bool bTest = false;
	
	UPROPERTY(EditAnywhere, Category="SN|Attack")
	UPlayMontageCallbackProxy* MontageProxy = nullptr;
	
	UPROPERTY(EditAnywhere, Category="SN|Attack")
	FGameplayTagContainer AttackCombo;
};
