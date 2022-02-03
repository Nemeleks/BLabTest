// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/BLabAIPerceptionComponent.h"

#include "AIController.h"
#include "Perception/AISense_Sight.h"

AActor* UBLabAIPerceptionComponent::GetEnemy() const
{
	TArray<AActor*> PercievedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);
	if (PercievedActors.Num() == 0)
	{
		return  nullptr;
	}

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller)
	{
		return nullptr;
	}

	const auto Pawn = Controller->GetPawn();
	if (!Pawn)
	{
		return nullptr;
	}

	float ClosestDistance = MAX_FLT;
	AActor* ClosestActor = nullptr;
	for	(const auto Actor : PercievedActors)
	{
		const auto CurrentDistance = (Actor->GetActorLocation()- Pawn->GetActorLocation()).Size();
		if (CurrentDistance < ClosestDistance)
		{
			ClosestDistance = CurrentDistance;
			ClosestActor = Actor;
		}
	}
	
	return ClosestActor;
}
