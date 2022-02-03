// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FindEnemyService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BLabAIPerceptionComponent.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UFindEnemyService::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto PerceptionComponent = Cast<UBLabAIPerceptionComponent>(Controller->GetComponentByClass(UBLabAIPerceptionComponent::StaticClass()));
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
