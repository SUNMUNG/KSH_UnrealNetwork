// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TestGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameOver);
/**
 * 
 */
UCLASS()
class KI7_UNREALNETWORK_API ATestGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ATestGameState();

protected:
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	inline float GetGameElapsedTime() const { return GameElapsedTime; }
	inline float GetGameOverTime() const { return GameOverTime; }

public:

	FOnGameOver OnGameOver;

protected:
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameElapsedTime = 0.0f;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = "Game Data")
	float GameOverTime = 5.0f;
private:
	bool isGameOver = false;

};
