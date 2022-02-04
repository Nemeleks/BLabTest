// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WeaponComponent.h"
#include "Weapons/BaseWeapon.h"


// Sets default values for this component's properties
UWeaponComponent::UWeaponComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UWeaponComponent::Fire()
{
	if (CurrentWeapon)
	{
		CurrentWeapon->Fire();
	}
}

void UWeaponComponent::SpawnWeapon(FVector SpawnLocation, FRotator SpawnRotation)
{
	if (WeaponClass)
	{
		FActorSpawnParameters Params;
		Params.Owner = GetOwner();
		CurrentWeapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass, SpawnLocation, SpawnRotation, Params);
		CurrentWeapon->SetActorEnableCollision(false);
		CurrentWeapon->SetInstigator(Cast<APawn>(GetOwner()));
	}
}

void UWeaponComponent::AttachToPlayer(AActor* Player)
{
	if (CurrentWeapon)
	{
		CurrentWeapon->AttachToActor(Player, FAttachmentTransformRules::KeepRelativeTransform);
	}
}


