// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BLabTestGameModeBase.h"

#include "AI/AISpawnPoint.h"

void ABLabTestGameModeBase::NewRound()
{
	ResetLevel();
	OnNewRound.Broadcast();
	RestartPlayer(GetWorld()->GetFirstPlayerController());
	if (AISpawnPoint)
	{
		AISpawnPoint->DestroyAI();
		AISpawnPoint->SpawnAI();
	}
}
