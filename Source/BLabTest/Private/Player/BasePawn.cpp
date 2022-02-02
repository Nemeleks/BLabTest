// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/BasePawn.h"

#include "BaseWeapon.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Player/Components/PlayerMovementComponent.h"
#include "Player/Components/Weapon/WeaponComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxCollider);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(BoxCollider);

	WeaponSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("WeaponSpawnComponent"));
	WeaponSpawnPoint->SetupAttachment(MeshComponent);

	WeaponComponent = CreateDefaultSubobject<UWeaponComponent>(TEXT("WeaponComponent"));

	MovementComponent = CreateDefaultSubobject<UPlayerMovementComponent>(TEXT("MovementComponent"));

}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (WeaponComponent)
	{
		WeaponComponent->SpawnWeapon(WeaponSpawnPoint->GetRelativeLocation(), WeaponSpawnPoint->GetRelativeRotation());
		WeaponComponent->AttachToPlayer(this);
	}
	
}

void ABasePawn::Fire()
{
	if (WeaponComponent)
	{
		WeaponComponent->Fire();
	}
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

