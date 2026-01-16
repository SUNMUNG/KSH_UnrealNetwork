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

	if (DisconnectButton)
	{
		DisconnectButton->OnClicked.AddDynamic(this, &UCreateServerMainWidget::OnDisconnectButtonClicked);
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

void UCreateServerMainWidget::OnDisconnectButtonClicked()
{
	UTestMultiplayGameInstance* Instance = Cast<UTestMultiplayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (Instance)
	{
		Instance->DisconnectServer();
	}
}



void UCreateServerMainWidget::OnCreateButtonClicked()
{
	UTestMultiplayGameInstance* Instance = Cast<UTestMultiplayGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (Instance)
	{
		Instance->CreateServer();
	}
}
