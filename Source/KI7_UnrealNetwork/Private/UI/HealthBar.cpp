// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HealthBar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UHealthBar::SetCurrent(float InCurrent)
{
	if (Current)
	{
		Current->SetText(FText::AsNumber(InCurrent));
	}
}

void UHealthBar::SetMax(float InMax)
{
	if (Max)
	{
		Max->SetText(FText::AsNumber(InMax));
	}
}

void UHealthBar::SetHealthBar(float Inratio)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Inratio);
	}
}
