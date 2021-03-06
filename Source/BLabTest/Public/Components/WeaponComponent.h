// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponComponent.generated.h"

class ABaseWeapon;
class UArrowComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BLABTEST_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<ABaseWeapon> WeaponClass;

public:

	void Fire();

	void SpawnWeapon(FVector SpawnLocation, FRotator SpawnRotation);

	void AttachToPlayer(AActor* Player);

private:

	UPROPERTY()
	ABaseWeapon* CurrentWeapon = nullptr;

	
};
