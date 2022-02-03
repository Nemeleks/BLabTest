// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Controller/EnemyAIController.h"

#include "BaseWeapon.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "Enemy/EnemyPawn.h"
#include "Kismet/KismetSystemLibrary.h"

void AEnemyAIController::BeginPlay()
{
	Super::BeginPlay();

	EnemyPawn = Cast<AEnemyPawn>(GetPawn());
	NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	GetRandomPoint();
}

void AEnemyAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (EnemyPawn)
	{
	
		Targeting();
		if (bIsAttacking)
		{
			UE_LOG(LogTemp, Warning, TEXT("TRUE"));
		}
		if (!bIsAttacking)
		{
			UE_LOG(LogTemp, Warning, TEXT("FALSE"));
			MoveToNextPoint();
		}
		
	}
}

void AEnemyAIController::Targeting()
{
	FVector EnemyLocation = EnemyPawn->GetActorLocation();
	FVector EnemyForwardVector = EnemyPawn->GetActorForwardVector();
	FVector TraceEnd = EnemyLocation + EnemyForwardVector * 2000;
	FHitResult HitResult;
	TArray<AActor*> ActorsToIgnore;
	EnemyPawn->GetAttachedActors(ActorsToIgnore);
	ActorsToIgnore.Add(EnemyPawn);
	if (UKismetSystemLibrary::SphereTraceSingle(GetWorld(),EnemyLocation, TraceEnd, 15.f, ETraceTypeQuery::TraceTypeQuery2,
		false,ActorsToIgnore, EDrawDebugTrace::Type::ForOneFrame, HitResult, false ))
	{
		if (HitResult.Actor == GetWorld()->GetFirstPlayerController()->GetPawn())
		{
			bIsAttacking = true;
			UE_LOG(LogTemp, Warning, TEXT("Hit"));
			EnemyPawn->Shoot();
			EnemyPawn->MoveF(0.f);
		}
		else
		{
			bIsAttacking = false;
		}
	}
	else
	{
		bIsAttacking = false;
	}
}

void AEnemyAIController::MoveToNextPoint()
{
	FVector PawnLocation = EnemyPawn->GetActorLocation();
	FVector MoveDirection = NextPoint - PawnLocation;
	MoveDirection.Normalize();
	FVector ForwardDirection = EnemyPawn->GetActorForwardVector();
	FVector RightDirection = EnemyPawn->GetActorRightVector();
	FVector TraceEnd = PawnLocation + ForwardDirection * 500.f;
	
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(EnemyPawn);
	TArray<AActor*> Attached;
	EnemyPawn->GetAttachedActors(Attached);
	Attached.Add(EnemyPawn);
	Params.AddIgnoredActors(Attached);
	FVector HalfSize = FVector(60.f,60.f,60.f);

	if (UKismetSystemLibrary::BoxTraceSingle(GetWorld(), PawnLocation, TraceEnd, HalfSize, EnemyPawn->GetActorRotation(), ETraceTypeQuery::TraceTypeQuery1, false, Attached, EDrawDebugTrace::Type::ForOneFrame,
		HitResult, false))
	{
		if (BlockingActor != HitResult.GetActor())
		{
			BlockingActor = HitResult.GetActor();
			HitNormal = HitResult.ImpactNormal;
			HitNormal.Normalize();
		}
	}
	if (BlockingActor)
	{
		FVector HitActorDirection = BlockingActor->GetActorLocation() - PawnLocation;
		HitActorDirection.Normalize();

		float ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardDirection, HitNormal)));
		float RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightDirection, HitNormal)));
		//UE_LOG(LogTemp, Warning, TEXT("ForwardAngle = %f"), ForwardAngle);
		//UE_LOG(LogTemp, Warning, TEXT("RightAngle = %f"), RightAngle);
		
		float RotationValue = 0.f;
		if (ForwardAngle > 90.f)
		{
			RotationValue = 1.f;
		}
		else
		{
			BlockingActor = nullptr;
		}
		 if (RightAngle > 90.f)
		 {
		 	RotationValue = -RotationValue;
		 }
		EnemyPawn->Rotate(RotationValue);
		EnemyPawn->MoveF(1.f);
	}
	
	else
	{
		if (FVector::DistSquared(PawnLocation, NextPoint) <= FMath::Square(MovementAccuracy))
		{
			GetRandomPoint();
		}

		DrawDebugLine(GetWorld(), PawnLocation, TraceEnd, FColor::Green, false, 0.1f, 0, 5.f);

		float ForwardAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardDirection, MoveDirection)));
		float RightAngle = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(RightDirection, MoveDirection)));

		float RotationValue = 0.f;
		if (ForwardAngle > 5.f)
		{
			RotationValue = 1.f;
		}
		if (RightAngle > 90.f)
		{
			RotationValue = -RotationValue;
		}
		EnemyPawn->Rotate(RotationValue);
		if (ForwardAngle < 20.f)
		{
			EnemyPawn->MoveF(1.f);
		}
		else
		{
			EnemyPawn->MoveF(0.f);
		}
	}
}

void AEnemyAIController::GetRandomPoint()
{
	auto CurrentLocation = EnemyPawn->GetActorLocation();
	FNavLocation NavLocation;
	NavigationSystem->GetRandomPointInNavigableRadius(CurrentLocation, NextPointRadius, NavLocation );
	NextPoint.X = NavLocation.Location.X;
	NextPoint.Y = NavLocation.Location.Y;
	NextPoint.Z = 102.f;
	
}
