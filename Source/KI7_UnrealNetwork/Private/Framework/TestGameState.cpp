// Fill out your copyright notice in the Description page of Project Settings.


#include "Framework/TestGameState.h"
#include "Net/UnrealNetwork.h"

ATestGameState::ATestGameState()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATestGameState::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		GameElapsedTime += DeltaTime;

		if (!isGameOver) {
			if (GameOverTime >= 0.0f)
			{
				GameOverTime -= DeltaTime;
				UE_LOG(LogTemp, Log, TEXT("GameOverTime : %.2f"), GameOverTime);
			}
			else {
				GameOverTime = 0.0f;
				isGameOver = true;
				OnGameOver.Broadcast();
				UE_LOG(LogTemp, Log, TEXT("GameOver"));
			}
		}
		
		
		UE_LOG(LogTemp, Log, TEXT("Time update : %.2f"), GameElapsedTime);

	}
}

void ATestGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATestGameState, GameElapsedTime);
	DOREPLIFETIME(ATestGameState, GameOverTime);
}
