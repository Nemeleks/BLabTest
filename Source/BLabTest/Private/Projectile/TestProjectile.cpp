// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile/TestProjectile.h"


// Sets default values
ATestProjectile::ATestProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	SetRootComponent(StaticMeshComponent);
	StaticMeshComponent->OnComponentHit.AddDynamic(this, &ThisClass::ATestProjectile::OnComponentHit);
}

// Called when the game starts or when spawned
void ATestProjectile::BeginPlay()
{
	Super::BeginPlay();
	StartForwardVector = GetActorForwardVector();
}

// Called every frame
void ATestProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector NewLocation = GetActorLocation() + StartForwardVector * MoveSpeed * DeltaTime;
	SetActorLocation(NewLocation, true);
}

void ATestProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit!"));
	if (GetInstigator())
	{
		UE_LOG(LogTemp, Warning, TEXT("Instigator = %s"), *GetInstigator()->GetName());
	}

	StartForwardVector = FMath::GetReflectionVector(StartForwardVector, HitResult.Normal);
}