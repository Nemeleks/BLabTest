// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BaseCharacter.h"

#include "Components/ArrowComponent.h"
#include "Player/Components/Weapon/WeaponComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("WeaponSpawnComponent"));
	WeaponSpawnPoint->SetupAttachment(RootComponent);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponComponent)
	{
		WeaponComponent->SpawnWeapon(WeaponSpawnPoint->GetRelativeLocation(), WeaponSpawnPoint->GetRelativeRotation());
		WeaponComponent->AttachToPlayer(this);
	}
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::Fire()
{
	if (WeaponComponent)
	{
		WeaponComponent->Fire();
	}
}

// Called to bind functionality to input
void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

