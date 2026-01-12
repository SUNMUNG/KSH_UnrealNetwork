// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/ReplicationCharacter.h"
#include "Net/UnrealNetwork.h"
// Sets default values
AReplicationCharacter::AReplicationCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AReplicationCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReplicationCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FString Str = FString::Printf(TEXT("Lv(%d), Exp(%.1f), Health(%.1f)"),Level,Exp,Health);
	DrawDebugString(GetWorld(), GetActorLocation(), Str, nullptr, FColor::White, 0.0f, true);

}

// Called to bind functionality to input
void AReplicationCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AReplicationCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AReplicationCharacter, Health); // Health 는 모두에게 리플리케이션
	DOREPLIFETIME_CONDITION(AReplicationCharacter, Level, COND_OwnerOnly); // 오너에게만 리플리케이션
	DOREPLIFETIME_CONDITION(AReplicationCharacter, Exp, COND_SimulatedOnly); // 오너 제외한 나머지에게  리플리케이션
}

void AReplicationCharacter::OnRepNotify_Level()
{
	const FString Str = FString::Printf(TEXT("서버에서 레벨을 %d로 변경했다."),Level);
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Yellow, Str);
}

void AReplicationCharacter::TestSetLevel(int32 inLevel)
{
	if (HasAuthority()) {
		Level = inLevel;
	}
}

void AReplicationCharacter::TestSetHealth(float inHealth)
{
	if (HasAuthority()) {
		Health = inHealth;
	}
}

void AReplicationCharacter::TestSetExp(float inExp)
{
	if (HasAuthority()) {
		Exp = inExp;
	}
}

