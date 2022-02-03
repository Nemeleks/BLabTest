// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "BLabAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class BLABTEST_API UBLabAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
	AActor* GetEnemy() const;
};
