// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/SetStaticEnemyService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

USetStaticEnemyService::USetStaticEnemyService()
{
	NodeName = "Set Static Enemy";
}

void USetStaticEnemyService::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void USetStaticEnemyService::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void USetStaticEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return;
	}

	if (const auto Pawn = GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, Pawn);
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
