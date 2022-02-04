// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystems/ActorPoolSubsystem.h"

void UActorPoolSubsystem::OnActorDestroyed(AActor* Actor)
{
	check(IsActorInPool(Actor));
	TArray<AActor*>* Pool = InactiveActors.Find(Actor->GetClass());
	if (Pool && Pool->Contains(Actor))
	{
		Pool->Remove(Actor);
	}
	Actors.Remove(Actor);
}

bool UActorPoolSubsystem::DoesSupportWorldType(EWorldType::Type WorldType) const
{
	return (WorldType == EWorldType::Game || WorldType == EWorldType::PIE);
}

bool UActorPoolSubsystem::IsActorInPool(AActor* Actor) const
{
	return Actors.Contains(Actor);
}

void UActorPoolSubsystem::MoveActorToPool(AActor* Actor)
{
	if (!Actor || !IsActorInPool(Actor)) return;


	TArray<AActor*>& Pool = InactiveActors.FindOrAdd(Actor->GetClass());
	if (!Pool.Contains(Actor))
	{
		Actor->SetActorTickEnabled(false);
		Pool.Add(Actor);
	}
}

AActor* UActorPoolSubsystem::MoveActorFromPool(UClass* Class, const FTransform& Transform)
{
	if (!Class) return nullptr;

	TArray<AActor*>* Pool = InactiveActors.Find(Class);
	AActor* ActorToMove = nullptr;
	if (Pool && Pool->Num() > 0)
	{
		ActorToMove = Pool->Pop();
		FVector CorrectScale = Transform.GetScale3D() * ActorToMove->GetActorScale();
		ActorToMove->SetActorTransform(FTransform(Transform.GetRotation(), Transform.GetLocation(), CorrectScale), false, nullptr, ETeleportType::ResetPhysics);
		ActorToMove->SetActorTickEnabled(true);
	}
	else
	{
		ActorToMove = GetWorld()->SpawnActor(Class, &Transform);
		if (!ActorToMove) return nullptr;
		Actors.Add(ActorToMove);
		ActorToMove->OnDestroyed.AddDynamic(this, &UActorPoolSubsystem::OnActorDestroyed);
	}

	return ActorToMove;
}

void UActorPoolSubsystem::DumpPoolStats()
{
	UE_LOG(LogTemp, Display, TEXT("NumActors in pool: %d"), Actors.Num());
	UE_LOG(LogTemp, Display, TEXT("InactiveActors in pool:"));
	UE_LOG(LogTemp, Display, TEXT("Actor\t\t\tClass"));
	UE_LOG(LogTemp, Display, TEXT("=====\t\t\t====="));
	for (const auto& Record : InactiveActors)
	{
		for (AActor* Actor : Record.Value)
		{
			UE_LOG(LogTemp, Display, TEXT("%s\t\t\t%s"), *Actor->GetName(), *Record.Key->GetName());
		}
	}
}