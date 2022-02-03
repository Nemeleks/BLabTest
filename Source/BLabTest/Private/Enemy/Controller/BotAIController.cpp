﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/BotAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BLabAIPerceptionComponent.h"
#include "Enemy/EnemyCharacter.h"


ABotAIController::ABotAIController()
{
	BLabAIPerceptionComponent = CreateDefaultSubobject<UBLabAIPerceptionComponent>(TEXT("BLabAIPerceprionComponent"));
	SetPerceptionComponent(*BLabAIPerceptionComponent);
}

void ABotAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	const auto Bot = Cast<AEnemyCharacter>(InPawn);
	if (Bot)
	{
		UE_LOG(LogTemp, Warning, TEXT("RunTree"));
		RunBehaviorTree(Bot->GetBehaviorTree());
	}
}

void ABotAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ABotAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) 
	{
		return nullptr;
	}
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}

