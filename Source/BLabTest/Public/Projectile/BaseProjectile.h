// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/EnemyCharacter.h"
#include "Engine/BlockingVolume.h"
#include "GameFramework/Actor.h"
#include "Player/PlayerCharacter.h"
#include "BaseProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class BLABTEST_API ABaseProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABaseProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION()
	virtual void OnComponentHit(class UPrimitiveComponent* HitComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, const FHitResult& HitResult);
	
	UFUNCTION()
	void OnProjectileStop( const FHitResult& ImpactResult);

	void FireInDirection(const FVector& ShootDirection);
};

