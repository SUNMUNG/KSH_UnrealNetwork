// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CreateServerMainWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Framework/TestMultiplayGameInstance.h"
#include "Components/Button.h"
#include "Components/EditableText.h"
void UCreateServerMainWidget::NativeConstruct()
{
	
	Super::NativeConstruct();
	if (CreateButton)
	{
		CreateButton->OnClicked.AddDynamic(this, &UCreateServerMainWidget::OnCreateButtonClicked);
	}

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &UCreateServerMainWidget::OnJoinButtonClicked);
	}

	if (InputIPAddress)
	{
		InputIPAddress->OnTextCommitted.AddDynamic(this, &UCreateServerMainWidget::OnTextComiited);
	}
}


void UCreateServerMainWidget::OnJoinButtonClicked()
{
	UTestMultiplayGameInstance* Instance = Cast<UTestMultiplayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (Instance)
	{
		FString IPAddress = Instance->GetIPAddress();
		if (InputIPAddress)
		{
			FString InputIP = InputIPAddress->GetText().ToString();

			if (!InputIP.IsEmpty())
			{
				IPAddress = InputIP;
			}
		}
		Instance->JoinServer(IPAddress);
	}

}

void UCreateServerMainWidget::OnTextComiited(const FText& NewText, ETextCommit::Type InTextCommit)
{
}


void UCreateServerMainWidget::OnCreateButtonClicked()
{
	UTestMultiplayGameInstance* Instance = Cast<UTestMultiplayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (Instance)
	{
		Instance->CreateServer();
	}
}
