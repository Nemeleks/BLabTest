// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BLabTestGameModeBase.h"

#include "AI/AISpawnPoint.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

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

void ABLabTestGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (Controller)
	{
		Controller->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetInputMode_GameOnly(Controller);
	}
}
