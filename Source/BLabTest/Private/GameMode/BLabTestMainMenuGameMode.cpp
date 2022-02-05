// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/BLabTestMainMenuGameMode.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "UI/MainMenuWidget.h"


// Called when the game starts or when spawned
void ABLabTestMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	const auto Controller = GetWorld()->GetFirstPlayerController();
	if (!Controller || !MainMenuWidgetClass)
	{
		return;
	}
	Controller->SetShowMouseCursor(true);
	UWidgetBlueprintLibrary::SetInputMode_UIOnlyEx(Controller);
	MainMenuWidget = CreateWidget<UMainMenuWidget>(GetWorld(), MainMenuWidgetClass);
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();
	}
}
