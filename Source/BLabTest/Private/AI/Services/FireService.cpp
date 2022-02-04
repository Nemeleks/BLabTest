// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FireService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/WeaponComponent.h"

UFireService::UFireService()
{
	NodeName = "Fire";
}

void UFireService::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UFireService::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard)
	{
		return;
	}

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (const auto WeaponComponent = Cast<UWeaponComponent>(Controller->GetPawn()->GetComponentByClass(UWeaponComponent::StaticClass())))
	{
		if (HasAim)
		{
			UE_LOG(LogTemp, Warning, TEXT("Fire!"));
			WeaponComponent->Fire();
		}
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
