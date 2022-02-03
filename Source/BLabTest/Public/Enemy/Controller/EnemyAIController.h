// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

class AEnemyPawn;
class UNavigationSystemV1;

UCLASS()
class BLABTEST_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected:
	
	UPROPERTY()
	AEnemyPawn* EnemyPawn = nullptr;;
	
	UPROPERTY()
	AActor* BlockingActor = nullptr;

	UPROPERTY()
	UNavigationSystemV1* NavigationSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Movement")
	float NextPointRadius = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI|Movement")
	float MovementAccuracy = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float TargetingRange = 2000.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Targeting")
	float Accuracy = 10.f;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void Targeting();

	void MoveToNextPoint();

	void GetRandomPoint();

	FVector NextPoint = FVector::ZeroVector;

	FVector HitNormal;

private:
	
	bool bIsAttacking;
	
};
