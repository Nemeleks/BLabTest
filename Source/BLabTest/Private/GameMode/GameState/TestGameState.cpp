// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/GameState/TestGameState.h"

void ATestGameState::BeginPlay()
{
	Super::BeginPlay();

	PlayerScore = 0;
	EnemyScore = 0;
}
