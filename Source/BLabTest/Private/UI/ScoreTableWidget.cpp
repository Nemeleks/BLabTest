// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ScoreTableWidget.h"

#include "Components/TextBlock.h"
#include "GameState/TestGameState.h"

void UScoreTableWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UScoreTableWidget::Initialize()
{
	Super::Initialize();

	if (PlayerTeamScore)
	{
		PlayerTeamScore->TextDelegate.BindUFunction(this, "SetPlayerTeamScore");
	}
	if (EnemyTeamScore)
	{
		EnemyTeamScore->TextDelegate.BindUFunction(this, "SetEnemyTeamScore");
	}
	
	return true;
}

FText UScoreTableWidget::SetPlayerTeamScore()
{
	if (const auto GameState = Cast<ATestGameState>(GetWorld()->GetGameState()))
	{
		return FText::FromString(FString::FromInt(GameState->GetPlayerScore()));
	}
	return FText::FromString("Error");
}

FText UScoreTableWidget::SetEnemyTeamScore()
{
	if (const auto GameState = Cast<ATestGameState>(GetWorld()->GetGameState()))
	{
		return FText::FromString(FString::FromInt(GameState->GetEnemyScore()));
	}

	return FText::FromString("Error");
}
