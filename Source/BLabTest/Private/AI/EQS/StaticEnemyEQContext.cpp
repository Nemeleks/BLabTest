// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/StaticEnemyEQContext.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UStaticEnemyEQContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	//Super::ProvideContext(QueryInstance, ContextData);
	const auto QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!Blackboard)
	{
		return;
	}
	const auto ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(ContextActor));
}
