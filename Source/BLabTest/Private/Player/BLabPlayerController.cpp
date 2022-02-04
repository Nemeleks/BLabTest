// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BLabPlayerController.h"

#include "Subsystems/ActorPoolSubsystem.h"

void ABLabPlayerController::DumpActorPoolStats()
{
	GetWorld()->GetSubsystem<UActorPoolSubsystem>()->DumpPoolStats();
}
