// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestMultiplayGameInstance.h"
#include "Kismet/GameplayStatics.h"
UTestMultiplayGameInstance::UTestMultiplayGameInstance()
{
	ServerIP = "127.0.0.1";
}

void UTestMultiplayGameInstance::Init()
{
	Super::Init();

	if (UEngine* engine = GetEngine())
	{
		engine->OnNetworkFailure().AddUObject(this, &UTestMultiplayGameInstance::HandleNetworkFailure);
		engine->OnTravelFailure().AddUObject(this, &UTestMultiplayGameInstance::HandleTravelFailure);
	}
}

void UTestMultiplayGameInstance::CreateServer()
{
	FString Mapname;
	if (!ServerLevelAsset.IsNull())
	{
		Mapname = ServerLevelAsset.GetLongPackageName();

	}
	else {
		Mapname = UGameplayStatics::GetCurrentLevelName(GetWorld());
	}
	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("world가 없습니다 !! 서버를 만들 수 없습니다."));
		return;
	}
	FString Options = FString::Printf(TEXT("listen?MaxPlayers=%d"), MaxPlayers);
	UE_LOG(LogTemp, Warning, TEXT("리슨서버 생성 : %s"), *Mapname);
	UGameplayStatics::OpenLevel(world, FName(*Mapname), true, Options);
	UE_LOG(LogTemp, Warning, TEXT("리슨서버 시작"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, TEXT("리슨서버 시작"));
	}
}




void UTestMultiplayGameInstance::JoinServer(FString IPAddress)
{
	if (IPAddress.IsEmpty())
	{
		IPAddress = ServerIP;
	}

	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("서버에 접속할 수 없습니다."));
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("플레이어 컨트롤러가 없습니다"));
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("서버에 접속합니다 : %s"), *IPAddress);
	PC->ClientTravel(IPAddress, ETravelType::TRAVEL_Absolute);

	UE_LOG(LogTemp, Warning, TEXT("서버 접속 시작"));
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, TEXT("서버 접속 시작"));
	}
}

void UTestMultiplayGameInstance::DisconnectServer()
{
	FString Mapname;
	if (!MainLevelAsset.IsNull())
	{
		Mapname = MainLevelAsset.GetLongPackageName();
		UE_LOG(LogTemp, Error, TEXT("MainLevelAsset가 없습니다 !!"));
	}
	else {
		return;
	}
	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("world가 없습니다 !!"));
		return;
	}
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (!PC)
	{
		UE_LOG(LogTemp, Error, TEXT("플레이어 컨트롤러가 없습니다"));
		return;
	}
	
	UE_LOG(LogTemp, Error, TEXT("서버에서 나가는 중입니다..."));
	PC->ClientTravel(Mapname, ETravelType::TRAVEL_Absolute);
	UE_LOG(LogTemp, Error, TEXT("서버 접속 해제"));

	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, TEXT("리슨서버 연결끊어짐"));
	}


}

void UTestMultiplayGameInstance::HandleNetworkFailure(UWorld* World, UNetDriver* NetDriver, ENetworkFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogNet, Error, TEXT("HandleNetworkFailure 실행"));
	UE_LOG(LogNet, Error, TEXT("오류 타입 : %d"),(int32)FailureType);
	UE_LOG(LogNet, Error, TEXT("오류 메세지 : %s"),*ErrorString);
	


}

void UTestMultiplayGameInstance::HandleTravelFailure(UWorld* World, ETravelFailure::Type FailureType, const FString& ErrorString)
{
	UE_LOG(LogNet, Error, TEXT("HandleTravelFailure 실행"));
	UE_LOG(LogNet, Error, TEXT("오류 타입 : %d"), (int32)FailureType);
	UE_LOG(LogNet, Error, TEXT("오류 메세지 : %s"), *ErrorString);

	switch (FailureType)
	{
	case ETravelFailure::ServerTravelFailure:
		if (ErrorString.Contains(TEXT("Full")) || ErrorString.Contains(TEXT("full")))
		{
			UE_LOG(LogNet, Error, TEXT("서버가 가득찼다."));
		}
			break;
	default:
		break;
	}
}