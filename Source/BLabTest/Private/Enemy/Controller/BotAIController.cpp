// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/BotAIController.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Enemy/EnemyCharacter.h"


// Called when the game starts or when spawned
void ABotAIController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABotAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
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

