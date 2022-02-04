// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTaskRicochetAttack.generated.h"

/**
 * 
 */
UCLASS()
class BLABTEST_API UBTTaskRicochetAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskRicochetAttack();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
