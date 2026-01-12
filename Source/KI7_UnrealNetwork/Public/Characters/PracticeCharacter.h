// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputAction.h"
#include "PracticeCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnExpChanged, float, InExp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLevelChanged, int32, InLevel);

UCLASS()
class KI7_UNREALNETWORK_API APracticeCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APracticeCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	UFUNCTION()
	void AddHealth();

	UFUNCTION(Server, Reliable)
	void ServerAddHealth();

	UFUNCTION()
	void AddExp();

	UFUNCTION(Server, Reliable)
	void ServerAddExp();

	UFUNCTION()
	void AddLevel();

	UFUNCTION(Server, Reliable)
	void ServerAddLevel();


	UFUNCTION()
	void AddMaxHealth();

	UFUNCTION(Server, Reliable)
	void ServerAddMaxHealth();

	UFUNCTION()
	void OnRepNotify_Health();

	UFUNCTION()
	void OnRepNotify_MaxHealth();

	UFUNCTION()
	void OnRepNotify_Level1();

	UFUNCTION()
	void OnRepNotify_Exp();

public:
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepNotify_Level1)
	int32 Level = 1;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepNotify_Health)
	float Health = 100.0f;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepNotify_MaxHealth)
	float MaxHealth = 100.0f;

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRepNotify_Exp)
	float Exp = 0.0f;

	UPROPERTY(BlueprintAssignable)
	FOnExpChanged OnExpChanged;
	UPROPERTY(BlueprintAssignable)
	FOnLevelChanged OnLevelChanged;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Health = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_MaxHealth = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Exp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> IA_Level = nullptr;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	TObjectPtr<class UWidgetComponent> HealthBar = nullptr;


private:
	UPROPERTY()
	TObjectPtr<class UHealthBar> BarWidget = nullptr;
};
