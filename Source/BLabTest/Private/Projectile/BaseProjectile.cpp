// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);

	MeshComponent->OnComponentHit.AddDynamic(this, &ThisClass::ABaseProjectile::OnComponentHit);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovementComponent->OnProjectileStop.AddDynamic(this, &ABaseProjectile::OnProjectileStop);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::OnProjectileStop(const FHitResult& ImpactResult)
{
	Destroy();
}

void ABaseProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	if (const auto BlockingVolume = Cast<ABlockingVolume>(OtherActor))
	{
		Destroy();
	}
	if (const auto BotPawn = Cast<AEnemyCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Enemy"));
	}
	if (const auto PlayerPawn = Cast<APlayerCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit Player"));
	}
}