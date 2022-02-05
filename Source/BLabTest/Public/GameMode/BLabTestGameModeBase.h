// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BLabTestGameModeBase.generated.h"

class AAISpawnPoint;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnNewRound);

UCLASS()
class BLABTEST_API ABLabTestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	void NewRound();
	void SetAISpawnPoint(AAISpawnPoint* InPoint){AISpawnPoint = InPoint;}
	
	FOnNewRound OnNewRound;
protected:

	virtual void BeginPlay() override;
	
	UPROPERTY()
	AAISpawnPoint* AISpawnPoint = nullptr;

	

	
};
