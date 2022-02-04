// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "FindRicochetService.generated.h"

/**
 * 
 */
UCLASS()
class BLABTEST_API UFindRicochetService : public UBTService
{
	GENERATED_BODY()

public:
	UFindRicochetService();
	
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector RicochetAttackKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int32 MaxRicochets = 3;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float TraceDistance = 3000.f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
