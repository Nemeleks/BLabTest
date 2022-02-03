// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScoreTableWidget.generated.h"

class UTextBlock;

UCLASS()
class BLABTEST_API UScoreTableWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerTeamScore;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyTeamScore;

private:

	UFUNCTION()
	FText SetPlayerTeamScore();

	UFUNCTION()
	FText SetEnemyTeamScore();
};
