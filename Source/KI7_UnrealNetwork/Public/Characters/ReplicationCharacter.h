// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ReplicationCharacter.generated.h"

UCLASS()
class KI7_UNREALNETWORK_API AReplicationCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AReplicationCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void OnRepNotify_Level();

public:
	UFUNCTION(BlueprintCallable)
	void TestSetLevel(int32 inLevel);

	UFUNCTION(BlueprintCallable)
	void TestSetHealth(float inHealth);

	UFUNCTION(BlueprintCallable)
	void TestSetExp(float inExp);

	UPROPERTY(ReplicatedUsing = OnRepNotify_Level) //Level 이 리플리케이션될때마다 OnRepNotify_Level실행
	int32 Level = 1;

	UPROPERTY(Replicated)//리플리케이션이되지만 실행되는 함수없다
	float Health = 100.0f;

	UPROPERTY(Replicated)
	float Exp = 0.0f;

public:	


};
