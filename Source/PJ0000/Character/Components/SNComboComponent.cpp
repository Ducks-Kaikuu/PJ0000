// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ0000/Character/Components/SNComboComponent.h"

#include "ChooserFunctionLibrary.h"
#include "PlayMontageCallbackProxy.h"
#include "SNDef.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "GameFramework/Character.h"
#include "PoseSearch/PoseSearchLibrary.h"

// Sets default values for this component's properties
USNComboComponent::USNComboComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void USNComboComponent::Start()
{
	MontageProxyInstance = PerformMotionMatching(Cast<ACharacter>(GetOwnerActor()));

	if (MontageProxyInstance != nullptr)
	{
		MontageProxyInstance->OnCompleted.AddDynamic(this, &USNComboComponent::OnMontagePlayEnd);
		MontageProxyInstance->OnInterrupted.AddDynamic(this, &USNComboComponent::OnMontagePlayEnd);
		MontageProxyInstance->OnBlendOut.AddDynamic(this, &USNComboComponent::OnMontagePlayEnd);
	}
}

void USNComboComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (HasMatchingGameplayTag(BranchTag) == true)
	{
		if (bAdvancedInput == true)
		{
			bAdvancedInput = false;

			if (MontageProxyInstance != nullptr)
			{
				MontageProxyInstance->OnCompleted.RemoveDynamic(this, &USNComboComponent::OnMontagePlayEnd);
				MontageProxyInstance->OnInterrupted.RemoveDynamic(this, &USNComboComponent::OnMontagePlayEnd);
				MontageProxyInstance->OnBlendOut.RemoveDynamic(this, &USNComboComponent::OnMontagePlayEnd);
			}
			
			MontageProxyInstance = PerformMotionMatching(Cast<ACharacter>(GetOwnerActor()));

			RemoveLooseGameplayTag(BranchTag);
			
			if (MontageProxyInstance != nullptr)
			{
				MontageProxyInstance->OnCompleted.AddDynamic(this, &USNComboComponent::OnMontagePlayEnd);
				MontageProxyInstance->OnInterrupted.AddDynamic(this, &USNComboComponent::OnMontagePlayEnd);
				MontageProxyInstance->OnBlendOut.AddDynamic(this, &USNComboComponent::OnMontagePlayEnd);
			} else
			{
				ComboScore = 0.0f;
	
				SetComponentTickEnabled(false);			
			}
		}
	}
}

void USNComboComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);
}

void USNComboComponent::OnMontagePlayEnd(FName NotiryName)
{
	ComboScore = 0.0f;
	
	SetComponentTickEnabled(false);
}

UPlayMontageCallbackProxy* USNComboComponent::PerformMotionMatching(ACharacter* Character)
{
	if (AttackAnimationChooser != nullptr)
	{
		//! チューザーを評価する
		FChooserEvaluationContext Context = UChooserFunctionLibrary::MakeChooserEvaluationContext();
		//! ChooserTable評価用の構造体を設定(ChooserTable側に設定している構造体の型と同じもの)
		Context.AddObjectParam(this);

		FInstancedStruct ChooserInstance = UChooserFunctionLibrary::MakeEvaluateChooser(AttackAnimationChooser);
		//! 評価を実行
		TArray<UObject*> Assets(UChooserFunctionLibrary::EvaluateObjectChooserBaseMulti(Context, ChooserInstance, UAnimMontage::StaticClass()));
		
		if(Assets.Num() <= 0){
			
			SNPLUGIN_WARNING(TEXT("Climb Motion is not find."));
			
			return nullptr;
		}
		
		UAnimInstance* AnimInstanceBase = Cast<UAnimInstance>(Character->GetMesh()->GetAnimInstance());
		
		FPoseSearchBlueprintResult PoseSearchResult;
		//! 選択されたモンタージュから最良のモンタージュを検索
		UPoseSearchLibrary::MotionMatch(AnimInstanceBase, Assets, FName(TEXT("PoseHistory")), FPoseSearchContinuingProperties(), FPoseSearchFutureProperties(), PoseSearchResult);
	
		const UAnimMontage* AnimMontage = Cast<UAnimMontage>(PoseSearchResult.SelectedAnimation != nullptr ? PoseSearchResult.SelectedAnimation : Assets[0]);
	
		if(AnimMontage == nullptr){
			//! データベースが無効かスキーマに問題がある可能性あり
			SNPLUGIN_ERROR(TEXT("Failed To Find Montage!"));
			
			return nullptr;
		}

		
		SNPLUGIN_WARNING(TEXT("Combo Score(%f)"), ComboScore);
		
		const UAnimMontage* ClimbMontage = Cast<const UAnimMontage>(AnimMontage);
		// モンタージュを再生
		UPlayMontageCallbackProxy* MontageProxy = UPlayMontageCallbackProxy::CreateProxyObjectForPlayMontage(Character->GetMesh(), const_cast<UAnimMontage*>(ClimbMontage), PoseSearchResult.WantedPlayRate, PoseSearchResult.SelectedTime, NAME_None);

		return MontageProxy;
	}

	return nullptr;
}

void USNComboComponent::ResetAbilityGameplayTags()
{
	GameplayTagCountContainer.Reset();
}

void USNComboComponent::AddAbilityTask(UAbilityTask* Task)
{
	if (Task != nullptr)
	{
		ComboTasks.Add(Task);	
	}

	if (ComboTasks.Num() > 0)
	{
		SetComponentTickEnabled(true);
	}
}

void USNComboComponent::RemoveAbilityTask(UAbilityTask* Task)
{
	ComboTasks.Remove(Task);
}



