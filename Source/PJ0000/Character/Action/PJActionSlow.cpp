// Fill out your copyright notice in the Description page of Project Settings.


#include "PJ0000/Character/Action/PJActionSlow.h"

#include "Kismet/GameplayStatics.h"

void UPJActionSlow::ExecAction(const FInputActionValue& InputActionValue)
{
	Super::ExecAction(InputActionValue);

	float InputValue = InputActionValue.Get<float>(), Value = 0.0f;

	Value = FMath::Clamp(1.0f - InputValue, SlowSpeed, 1.0f);
	
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), Value);
}
