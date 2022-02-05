// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BLabPlayerController.h"

#include "Kismet/GameplayStatics.h"
#include "Subsystems/ActorPoolSubsystem.h"

void ABLabPlayerController::DumpActorPoolStats()
{
	GetWorld()->GetSubsystem<UActorPoolSubsystem>()->DumpPoolStats();
}

void ABLabPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("MainMenu", IE_Pressed, this, &ThisClass::BackToMenu);
}

void ABLabPlayerController::BackToMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), "MainMenu");
}
