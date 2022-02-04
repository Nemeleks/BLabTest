// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/FindRicochetService.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindRicochetService::UFindRicochetService()
{
	NodeName = "Find Ricochet";
}

void UFindRicochetService::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);
}

void UFindRicochetService::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskDeactivated(Task);
}

void UFindRicochetService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Blackboard && !Controller)
	{
		return;
	}
	
	const auto AICharacter = Controller->GetPawn();
	
	if (AICharacter)
	{
		FHitResult StartHit;
		FVector TraceStart = AICharacter->GetActorLocation();
		FVector ForwardDirection = AICharacter->GetActorForwardVector();
		FVector TraceEnd = TraceStart + ForwardDirection * 4000;
		FCollisionQueryParams Params;
		TArray<AActor*> AttachedActors;
		AICharacter->GetAttachedActors(AttachedActors);
		Params.AddIgnoredActor(AICharacter);
		Params.AddIgnoredActors(AttachedActors);
		
		if (GetWorld()->LineTraceSingleByChannel(StartHit, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility,Params))
		{
			FHitResult PreviousHit = StartHit;
			DrawDebugLine(GetWorld(),TraceStart,TraceEnd, FColor::Red);
			for (int32 i = 0; i < 4; ++i)
			{
				if (PreviousHit.bBlockingHit)
				{
					FVector Direction = PreviousHit.TraceEnd - PreviousHit.TraceStart;
					Direction.Normalize();
					FVector ReflectVector = FMath::GetReflectionVector(Direction, PreviousHit.Normal);
					FVector NewTraceStart = PreviousHit.ImpactPoint + ReflectVector;
					FVector NewTraceEnd = PreviousHit.ImpactPoint + ReflectVector*4000;
					if (GetWorld()->LineTraceSingleByChannel(PreviousHit, NewTraceStart, NewTraceEnd, ECollisionChannel::ECC_Visibility,Params))
					{
						if (PreviousHit.Actor == GetWorld()->GetFirstPlayerController()->GetPawn())
						{
							Blackboard->SetValueAsBool(RicochetAttackKey.SelectedKeyName, true);
							UE_LOG(LogTemp,Warning,TEXT("i see player!"))
							break;
						}
					}
					DrawDebugLine(GetWorld(),NewTraceStart,NewTraceEnd, FColor::Red);
				}
				Blackboard->SetValueAsBool(RicochetAttackKey.SelectedKeyName, false);
			}
			
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
