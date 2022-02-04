// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestGameState.generated.h"

/**
 * 
 */
UCLASS()
class BLABTEST_API ATestGameState : public AGameStateBase
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

private:

	int32 PlayerScore;
	int32 EnemyScore;

public:
	void AddPlayerScore(int32 Amount){PlayerScore += Amount;}
	void AddEnemyScore(int32 Amount){EnemyScore += Amount;}

	int32 GetPlayerScore() const {return PlayerScore;}
	int32 GetEnemyScore() const {return EnemyScore;}
};
