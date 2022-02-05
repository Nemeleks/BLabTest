// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"

#include "FindClosesEnemyProjectileService.generated.h"

/**
 * 
 */
UCLASS()
class BLABTEST_API UFindClosesEnemyProjectileService : public UBTService
{
	GENERATED_BODY()

public:
	UFindClosesEnemyProjectileService();

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyProjectileKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float TraceRadius = 1500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float ProjectileSphereTraceRadius = 40;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
