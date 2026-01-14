// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageZone.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"

// Sets default values
ADamageZone::ADamageZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Collision"));
	SetRootComponent(Collision);


	Rangeparticle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Rangeparticle"));
	Rangeparticle->SetupAttachment(RootComponent);

	Collision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
}

// Called when the game starts or when spawned
void ADamageZone::BeginPlay()
{
	Super::BeginPlay();
	
	OnActorBeginOverlap.AddDynamic(this, &ADamageZone::OnOverlapActor);
    OnActorEndOverlap.AddDynamic(this, &ADamageZone::OnOverlapEndActor);
}

// Called every frame
void ADamageZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ADamageZone::OnOverlapActor(AActor* OverlappedActor, AActor* OtherActor)
{
    if (HasAuthority())
    {
        if (OtherActor && OtherActor->IsA(ACharacter::StaticClass()))
        {
            ACharacter* player = Cast<ACharacter>(OtherActor);

            if (player)
            {
                GetWorldTimerManager().ClearTimer(TickDamageHandle);

                GetWorldTimerManager().SetTimer(
                    TickDamageHandle,
                    [this,player]() {
                        UE_LOG(LogTemp, Warning, TEXT("[Server] %s가 %s 에게 데미지 적용"), *this->GetName(), *player->GetName());
                        UGameplayStatics::ApplyDamage(player, 10.0f, player->GetController(), this, UDamageType::StaticClass());
                    }, 
                    1.0f,
                    true,
                    0.0f
                    );
            }
        }
    }
}

void ADamageZone::OnOverlapEndActor(AActor* OverlappedActor, AActor* OtherActor)
{
    GetWorldTimerManager().ClearTimer(TickDamageHandle);
}

