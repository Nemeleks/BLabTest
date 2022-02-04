// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AISpawnPoint.h"

#include "AI/EnemyCharacter.h"
#include "Components/ArrowComponent.h"
#include "GameMode/BLabTestGameModeBase.h"


// Sets default values
AAISpawnPoint::AAISpawnPoint()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	if (!RootComponent)
	{
		USceneComponent* SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
		SetRootComponent(SceneComponent);
	}

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("AISpawnPoint"));
	SpawnPoint->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	SpawnAI();

	const auto GameMode = Cast<ABLabTestGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->SetAISpawnPoint(this);
	}
}

void AAISpawnPoint::SpawnAI()
{
	if (AICharacterClass)
	{
		const auto SpawnLocation = SpawnPoint->GetComponentLocation();
		const auto SpawnRotation = SpawnPoint->GetComponentRotation();
		AICharacter = GetWorld()->SpawnActor<AEnemyCharacter>(AICharacterClass, SpawnLocation, SpawnRotation);

	}
	
}

void AAISpawnPoint::DestroyAI()
{
	if (AICharacter)
	{
		AICharacter->Destroy();
	}

}

