// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ0000/Character/Action/PJAttackAction.h"

#include "AbilitySystemComponent.h"
#include "SNDef.h"
#include "GameFramework/Character.h"
#include "PJ0000/Character/Components/SNComboComponent.h"

void UPJAttackAction::ExecAction(const FInputActionValue& InputActionValue)
{
	Super::ExecAction(InputActionValue);

	ACharacter* Character(Cast<ACharacter>(GetOwner<ACharacter>()));

	if (Character != nullptr)
	{
		USNComboComponent* ComboComponent = Character->FindComponentByClass<USNComboComponent>();

		if (ComboComponent != nullptr)
		{
			if (ComboComponent->IsComponentTickEnabled() == false)
			{
				ComboComponent->SetComboScore(0.0f);

				ComboComponent->Start();
				
				ComboComponent->SetComponentTickEnabled(true);
			}

			if (ComboComponent->HasMatchingGameplayTag(AdvancedInput))
			{
				if (ComboComponent->IsAdvancedInput() == false)
				{
					float ComboScore = ComboComponent->GetComboScore();

					ComboScore += 1.0f;

					ComboComponent->SetComboScore(ComboScore);
				
					ComboComponent->SetAdvancedInput(true);

					ComboComponent->RemoveLooseGameplayTag(AdvancedInput);
					
					SNPLUGIN_LOG(TEXT("Advanced Input Coming. %f"), ComboScore);
				}
			} 
		}
	}
}
