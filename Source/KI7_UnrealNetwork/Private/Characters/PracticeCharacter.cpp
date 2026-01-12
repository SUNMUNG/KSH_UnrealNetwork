// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/PracticeCharacter.h"
#include "EnhancedInputComponent.h"
#include "UI/HealthBar.h"
#include "Components/WidgetComponent.h"
#include "Net/UnrealNetwork.h"
// Sets default values
APracticeCharacter::APracticeCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
	HealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBar->SetupAttachment(RootComponent);
	HealthBar->SetDrawSize(FVector2D(300.0f, 50.0f));
	HealthBar->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void APracticeCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	BarWidget = Cast<UHealthBar>(HealthBar->GetWidget());
	if (BarWidget)
	{
		BarWidget->SetCurrent(Health);
		BarWidget->SetMax(MaxHealth);
		BarWidget->SetHealthBar(Health/MaxHealth);
	}
	

}

// Called every frame
void APracticeCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FString Str = FString::Printf(TEXT("Lv(%d), Exp(%.1f), Health(%.1f)"), Level, Exp, Health);
	DrawDebugString(GetWorld(), GetActorLocation(), Str, nullptr, FColor::White, 0.0f, true);
}

void APracticeCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(APracticeCharacter, Health); // Health 는 모두에게 리플리케이션
	DOREPLIFETIME(APracticeCharacter, MaxHealth); // Health 는 모두에게 리플리케이션
	DOREPLIFETIME_CONDITION(APracticeCharacter, Level, COND_OwnerOnly); // 오너에게만 리플리케이션
	DOREPLIFETIME_CONDITION(APracticeCharacter, Exp, COND_OwnerOnly);
}

void APracticeCharacter::AddHealth()
{
	ServerAddHealth();
}

void APracticeCharacter::ServerAddHealth_Implementation()
{
	if (MaxHealth <= Health)
	{
		return;
	}
	else {
		Health += 5.0f;
	}
	

	if (GetNetMode() == NM_ListenServer)
	{
		OnRepNotify_Health();
	}
	
}

void APracticeCharacter::AddExp()
{
	ServerAddExp();
}

void APracticeCharacter::ServerAddExp_Implementation()
{
	Exp += 2.0f;

	if (GetNetMode() == NM_ListenServer)
	{
		OnRepNotify_Exp();
	}
}

void APracticeCharacter::AddLevel()
{
	ServerAddLevel();


}

void APracticeCharacter::AddMaxHealth()
{
	ServerAddMaxHealth();
}
void APracticeCharacter::ServerAddMaxHealth_Implementation()
{
	 MaxHealth += 10.0f;

	 if (GetNetMode() == NM_ListenServer)
	 {
		 OnRepNotify_MaxHealth();
	 }
}


void APracticeCharacter::OnRepNotify_Health()
{
	if (BarWidget)
	{
		BarWidget->SetCurrent(Health);
		BarWidget->SetHealthBar(Health / MaxHealth);
	}
}

void APracticeCharacter::OnRepNotify_MaxHealth()
{
	if (BarWidget)
	{
		BarWidget->SetMax(MaxHealth);
		BarWidget->SetHealthBar(Health / MaxHealth);
	}
}

void APracticeCharacter::OnRepNotify_Level1()
{
	UE_LOG(LogTemp, Warning, TEXT("OnRepNotify_Level1"));
	OnLevelChanged.Broadcast(Level);


}

void APracticeCharacter::OnRepNotify_Exp()
{
	OnExpChanged.Broadcast(Exp);
}


void APracticeCharacter::ServerAddLevel_Implementation()
{
	Level++;

	if (GetNetMode() == NM_ListenServer)
	{
		OnRepNotify_Level1();
	}
}

// Called to bind functionality to input
void APracticeCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (IA_Health)
		{
			EnhancedInputComponent->BindAction(IA_Health, ETriggerEvent::Started, this, &APracticeCharacter::AddHealth);
		}
		if (IA_MaxHealth)
		{
			EnhancedInputComponent->BindAction(IA_MaxHealth, ETriggerEvent::Started, this, &APracticeCharacter::AddMaxHealth);
		}
		if (IA_Exp)
		{
			EnhancedInputComponent->BindAction(IA_Exp, ETriggerEvent::Started, this, &APracticeCharacter::AddExp);
		}
		if (IA_Level)
		{
			EnhancedInputComponent->BindAction(IA_Level, ETriggerEvent::Started, this, &APracticeCharacter::AddLevel);
		}
	}
}

