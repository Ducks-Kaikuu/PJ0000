// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "Components/ActorComponent.h"
#include "SNComboComponent.generated.h"

class UPlayMontageCallbackProxy;
class UChooserTable;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PJ0000_API USNComboComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USNComboComponent();

	void Start();
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	UPlayMontageCallbackProxy* PerformMotionMatching(ACharacter* Character);

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(BlueprintThreadSafe))
	FGameplayTag GetComboTag() const { return ComboTag; }

	void SetComboTag(const FGameplayTag& NewComboTag) { ComboTag = NewComboTag; }

	UFUNCTION(BlueprintCallable, BlueprintPure, meta=(BlueprintThreadSafe))
	float GetComboScore() const { return ComboScore; }

	void SetComboScore(float NewComboScore) { ComboScore = NewComboScore; }
	
	void ResetAbilityGameplayTags();

	void AddAbilityTask(UAbilityTask* Task);

	void RemoveAbilityTask(UAbilityTask* Task);

	void SetAdvancedInput(bool Flag);

	bool IsAdvancedInput() const { return bAdvancedInput; }

protected:
	virtual void BeginPlay() override;
	
private:

	UFUNCTION()
	void OnMontagePlayEnd(FName NotiryName);
	
	UPROPERTY(EditDefaultsOnly, Category = "SN|Attack")
	TObjectPtr<UChooserTable> AttackAnimationChooser = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "SN|Attack")
	TArray<TSubclassOf<UGameplayAbility>> ComboAbility;

	UPROPERTY(EditDefaultsOnly, Category = "SN|Attack")
	FGameplayTag AdvancedInputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, Category = "SN|Attack")
	FGameplayTag BranchTag = FGameplayTag();

	UPROPERTY()
	UPlayMontageCallbackProxy* MontageProxyInstance = nullptr;
	
	UPROPERTY()
	FGameplayTag ComboTag;

	UPROPERTY()
	bool bAdvancedInput = false;

	UPROPERTY()
	float ComboScore = -1.0f;

	UPROPERTY()
	TArray<TObjectPtr<UAbilityTask>> ComboTasks;
};

FORCEINLINE void USNComboComponent::SetAdvancedInput(bool Flag)
{
	bAdvancedInput = Flag;
}