// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"

#include "Components/ArrowComponent.h"
#include "Subsystems/ActorPoolSubsystem.h"
#include "Weapons/Projectile/BaseProjectile.h"
#include "Weapons/Projectile/TestProjectile.h"


// Sets default values
ABaseWeapon::ABaseWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	SetRootComponent(MeshComponent);

	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::ABaseWeapon::OnComponentBeginOverlap);
	MeshComponent->OnComponentEndOverlap.AddDynamic(this, &ThisClass::ABaseWeapon::OnComponentEndOverlap);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(MeshComponent);
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::Fire()
{
	if (ProjectileClass &&bCanFire)
	{
		UActorPoolSubsystem* Pool = GetWorld()->GetSubsystem<UActorPoolSubsystem>();
		FTransform SpawnTransform(ProjectileSpawnPoint->GetComponentRotation(), ProjectileSpawnPoint->GetComponentLocation(), FVector::OneVector);
		ABaseProjectile* Projectile = Cast<ABaseProjectile>(Pool->MoveActorFromPool(ProjectileClass, SpawnTransform));

		if (Projectile)
		{
			Projectile->SetInstigator(GetInstigator());
			Projectile->Start(ProjectileSpawnPoint->GetForwardVector());
		}
		
	}
}

void ABaseWeapon::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != GetOwner())
	{
		bCanFire = false;
	}
}

void ABaseWeapon::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor != GetOwner())
	{
		bCanFire = true;
	}
}

