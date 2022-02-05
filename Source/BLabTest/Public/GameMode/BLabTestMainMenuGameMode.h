// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BLabTestMainMenuGameMode.generated.h"

class UMainMenuWidget;

UCLASS()
class BLABTEST_API ABLabTestMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Main Menu")
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;

private:
	UPROPERTY()
	UUserWidget* MainMenuWidget;
};
