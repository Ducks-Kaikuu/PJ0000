// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MotionMatching/Character/Action/SNActionAim.h"
#include "PJActionSlow.generated.h"

/**
 * 
 */
UCLASS()
class PJ0000_API UPJActionSlow : public USNActionAim
{
	GENERATED_BODY()

public:
	virtual void ExecAction(const FInputActionValue& InputActionValue) override;

private:
	UPROPERTY(EditAnywhere, Category = "SN|Action")
	float SlowSpeed = 0.1f;
};
