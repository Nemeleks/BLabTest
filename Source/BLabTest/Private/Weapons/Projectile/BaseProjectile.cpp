// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Projectile/BaseProjectile.h"

#include "AI/EnemyCharacter.h"
#include "Components/SphereComponent.h"
#include "Engine/BlockingVolume.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameMode/BLabTestGameModeBase.h"
#include "GameMode/GameState/TestGameState.h"
#include "Subsystems/ActorPoolSubsystem.h"


// Sets default values
ABaseProjectile::ABaseProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = false;
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComponent);
	MeshComponent->OnComponentHit.AddDynamic(this, &ThisClass::ABaseProjectile::OnComponentHit);
	//MeshComponent->SetHiddenInGame(true);

	

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
//	ProjectileMovementComponent->OnProjectileStop.AddDynamic(this, &ABaseProjectile::OnProjectileStop);
}

// Called when the game starts or when spawned
void ABaseProjectile::BeginPlay()
{
	Super::BeginPlay();

	const auto GameMode = Cast<ABLabTestGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->OnNewRound.AddDynamic(this, &ThisClass::SelfDestroy);
	}
}

// Called every frame
void ABaseProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseProjectile::Start(const FVector& FireDirection)
{
	PrimaryActorTick.SetTickFunctionEnable(true);
	ProjectileMovementComponent->SetComponentTickEnabled(true);
	MeshComponent->SetHiddenInGame(false);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	SetActorEnableCollision(true);
	ProjectileMovementComponent->Velocity = FireDirection * ProjectileMovementComponent->InitialSpeed;
}

void ABaseProjectile::Stop()
{
	PrimaryActorTick.SetTickFunctionEnable(false);
	ProjectileMovementComponent->SetComponentTickEnabled(false);
	MeshComponent->SetHiddenInGame(true);
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorEnableCollision(false);
	
	UActorPoolSubsystem* Pool = GetWorld()->GetSubsystem<UActorPoolSubsystem>();
	if (Pool->IsActorInPool(this))
	{
		Pool->MoveActorToPool(this);
	}
	else
	{
		Destroy();		
	}
}

void ABaseProjectile::OnProjectileStop(const FHitResult& ImpactResult)
{
	Stop();
}

void ABaseProjectile::OnComponentHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& HitResult)
{
	const auto GameMode = Cast<ABLabTestGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode)
	{
		return;
	}
	
	if (const auto BlockingVolume = Cast<ABlockingVolume>(OtherActor))
	{
		Stop();
	}
	
	if (const auto BotPawn = Cast<AEnemyCharacter>(OtherActor))
	{
		const auto GameState = Cast<ATestGameState>(GetWorld()->GetGameState());
		if (OtherActor != GetInstigator())
		{
			GameState->AddPlayerScore(1);
			GameMode->NewRound();
		}
	}
	
	if (const auto PlayerPawn = Cast<APlayerCharacter>(OtherActor))
	{
		const auto GameState = Cast<ATestGameState>(GetWorld()->GetGameState());

		if (OtherActor != GetInstigator())
		{
			GameState->AddEnemyScore(1);
			GameMode->NewRound();
		}
	}
}

void ABaseProjectile::SelfDestroy()
{
	Stop();
}