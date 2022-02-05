// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FindClosesEnemyProjectileService.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Weapons/Projectile/BaseProjectile.h"

UFindClosesEnemyProjectileService::UFindClosesEnemyProjectileService()
{
	NodeName = "Find Enemy Closest Projectile";
}

void UFindClosesEnemyProjectileService::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UFindClosesEnemyProjectileService::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UFindClosesEnemyProjectileService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	float DeltaSeconds)
{

	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard)
	{
		return;
	}
	const auto Pawn = Controller->GetPawn();
	if (Pawn)
	{
		const FVector PawnLocation = Pawn->GetActorLocation();
		TArray<AActor*> ActorsToIgnore;
		TArray<FHitResult> HitResults;
		Pawn->GetAttachedActors(ActorsToIgnore);
		if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), PawnLocation, PawnLocation, TraceRadius, ETraceTypeQuery::TraceTypeQuery2,
			false, ActorsToIgnore, EDrawDebugTrace::ForOneFrame, HitResults, true))
		{
			AActor* ClosestProjectile = nullptr;
			float ClosestDistance = TraceRadius;
			for (const auto HitResult : HitResults)
			{
				if (const auto Projectile = Cast<ABaseProjectile>(HitResult.Actor))
				{
					if (Projectile->GetInstigator() != Pawn)
					{
						TArray<FHitResult> ProjectileHits;
						FVector ProjectileLocation = Projectile->GetActorLocation();
						FVector ProjectileForwardDirection = Projectile->GetActorForwardVector();
						FVector TraceEnd = ProjectileLocation + ProjectileForwardDirection*TraceRadius;
						
						if (UKismetSystemLibrary::SphereTraceMulti(GetWorld(), ProjectileLocation, TraceEnd, ProjectileSphereTraceRadius, ETraceTypeQuery::TraceTypeQuery3,
							false,ActorsToIgnore, EDrawDebugTrace::ForOneFrame, ProjectileHits, true, FColor::Yellow, FColor::Blue))
						{
							for (const auto ProjectileHit : ProjectileHits)
							{
								if (ProjectileHit.Actor == Pawn)
								{
									if (FVector::DistSquared(PawnLocation, HitResult.Actor->GetActorLocation()) < FMath::Square(ClosestDistance))
									{
										ClosestProjectile = HitResult.GetActor();
										ClosestDistance = (HitResult.Actor->GetActorLocation() - PawnLocation).Size();
									}
								}
							}

						}
						
					}
				}
			}
			Blackboard->SetValueAsObject(EnemyProjectileKey.SelectedKeyName, ClosestProjectile);
		}
		
	}
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
