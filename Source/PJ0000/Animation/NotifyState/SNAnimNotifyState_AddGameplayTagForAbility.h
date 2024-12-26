// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SNAnimNotifyState_AddGameplayTagForAbility.generated.h"

/**
 * 
 */
UCLASS()
class PJ0000_API USNAnimNotifyState_AddGameplayTagForAbility : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;

	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
	
private:
	
	UPROPERTY(EditAnywhere, Category="SN|Abilities|Attack")
	FGameplayTagContainer AbilityTags = FGameplayTagContainer();

#if WITH_EDITORONLY_DATA
	UPROPERTY(EditAnywhere, Category="SN|Abilities|Attack")
	bool bDebugDraw = false;
#endif
};
