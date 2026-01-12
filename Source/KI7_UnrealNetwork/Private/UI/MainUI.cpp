// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainUI.h"
#include "Components/TextBlock.h"



void UMainUI::SetExp(float InExp)
{
	if (Exp)
	{
		Exp->SetText(FText::AsNumber(InExp));
	}
}

void UMainUI::SetCurrentLevel(int32 InLevel)
{
	if (Level)
	{
		Level->SetText(FText::AsNumber(InLevel));
	}
}
