// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BLabPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BLABTEST_API ABLabPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:

	UFUNCTION(Exec)
	void DumpActorPoolStats();

	virtual void SetupInputComponent() override;

	void BackToMenu();
};
