// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GameStateMainHudWidget.h"
#include "Framework/TestGameState.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

void UGameStateMainHudWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	UpdateTimeDisplay();
}

void UGameStateMainHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!CachedGameState.IsValid())
	{
		CachedGameState = Cast<ATestGameState>(UGameplayStatics::GetGameState(this));
	}

	if (GameOver)
	{
		GameOver->SetVisibility(ESlateVisibility::Hidden);
		UE_LOG(LogTemp, Warning, TEXT("Hidden"));
	}

	if (CachedGameState.IsValid())
	{
		CachedGameState->OnGameOver.AddDynamic(this, &UGameStateMainHudWidget::ToggleGameOver);
	}
}

void UGameStateMainHudWidget::UpdateTimeDisplay()
{
	if (CachedGameState.IsValid())
	{
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameElapsedTime());
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;

		TimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}

	if (CachedGameState.IsValid())
	{
		int32 Total = FMath::FloorToInt(CachedGameState->GetGameOverTime());
		int32 Minutes = Total / 60;
		int32 Seconds = Total % 60;

		RemainTimeText->SetText(FText::FromString(FString::Printf(TEXT("%02d:%02d"), Minutes, Seconds)));
	}
}

void UGameStateMainHudWidget::ToggleGameOver()
{
	if (GameOver)
	{
		GameOver->SetVisibility(ESlateVisibility::Visible);
		UE_LOG(LogTemp, Warning, TEXT("Visible"));
	}
}
