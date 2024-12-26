// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SNActionBase.h"
#include "PJSpeedUpAction.generated.h"

/**
 * 
 */
UCLASS()
class PJ0000_API UPJSpeedUpAction : public USNActionBase
{
	GENERATED_BODY()

public:
	virtual void ExecAction(const FInputActionValue& InputActionValue) override;
};
