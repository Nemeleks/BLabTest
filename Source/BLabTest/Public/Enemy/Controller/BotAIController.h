// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BotAIController.generated.h"

UCLASS()
class BLABTEST_API ABotAIController : public AAIController
{
	GENERATED_BODY()

protected:
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual void OnPossess(APawn* InPawn) override;
};
