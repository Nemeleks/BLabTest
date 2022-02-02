// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/BaseProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

		
	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Collider"));
	SphereCollider->SetupAttachment(RootComponent);
	RootComponent = SphereCollider;
	SphereCollider->SetSphereRadius(6.f);
	SphereCollider->IgnoreActorWhenMoving(this, true);
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseProjectile::OnComponentBeginOverlap);

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(SphereCollider);

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

void ABaseProjectile::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	
}

void ABaseProjectile::OnProjectileStop(const FHitResult& ImpactResult)
{
	Destroy();
}

void ABaseProjectile::FireInDirection(const FVector& ShootDirection)
{

	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}