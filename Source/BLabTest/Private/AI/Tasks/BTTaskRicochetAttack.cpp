// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/BTTaskRicochetAttack.h"

#include "AIController.h"
#include "AI/EnemyCharacter.h"

UBTTaskRicochetAttack::UBTTaskRicochetAttack()
{
	NodeName = "RicochetFire";
}

void UBTTaskRicochetAttack::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

EBTNodeResult::Type UBTTaskRicochetAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//return Super::ExecuteTask(OwnerComp, NodeMemory);
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard)
	{
		return EBTNodeResult::Failed;
	}
	const auto Pawn = Cast<AEnemyCharacter>(Controller->GetPawn());
	if (!Pawn)
	{
		return EBTNodeResult::Failed;
	}
	Pawn->Fire();
	return EBTNodeResult::Succeeded;
}
