// Fill out your copyright notice in the Description page of Project Settings.


#include "LavaStep.h"
#include "objbase.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "Monster.h"

ALavaStep::ALavaStep(){

    PrimaryActorTick.bCanEverTick = false;

    RootElement = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
    RootComponent = RootElement;

    DamageCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageCollision"));
    DamageCollision->SetupAttachment(RootComponent);
    DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DamageCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    DamageCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    CompletionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("CompletionCollision"));
    CompletionCollision->SetupAttachment(RootComponent);
    CompletionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CompletionCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    CompletionCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    MonsterActivateCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("MonsterCollision"));
    MonsterActivateCollision->SetupAttachment(RootComponent);
    MonsterActivateCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MonsterActivateCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    MonsterActivateCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    MonsterStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("MonsterInitialPosition"));
    MonsterStartPosition->SetupAttachment(RootComponent);
}
void ALavaStep::BeginPlay()
{
    Super::BeginPlay();
    for (AActor* obj : ActorsToHide)
    {
        if (obj)
        {
            obj->SetActorHiddenInGame(true);
            obj->SetActorTickEnabled(false);
            obj->SetActorEnableCollision(false);
        }
    }

    PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}
void ALavaStep::StartStep()
{
    for (AActor* obj : ActorsToHide)
    {
        if (obj)
        {
            obj->SetActorHiddenInGame(false);
            obj->SetActorTickEnabled(false);
            obj->SetActorEnableCollision(true);
        }
    }

    CompletionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MonsterActivateCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

    CompletionCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    MonsterActivateCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    DamageCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

    CompletionCollision->OnComponentBeginOverlap.AddDynamic(this, &ALavaStep::OnCompletionBoxBeginOverlap);
    DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &ALavaStep::OnDamageBoxBeginOverlap);
    MonsterActivateCollision->OnComponentBeginOverlap.AddDynamic(this, &ALavaStep::OnMonsterBoxBeginOverlap);
}

void ALavaStep::EndStep()
{
    CompletionCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    MonsterActivateCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    CompletionCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    MonsterActivateCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    DamageCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

    CompletionCollision->OnComponentBeginOverlap.RemoveDynamic(this, &ALavaStep::OnCompletionBoxBeginOverlap);
    DamageCollision->OnComponentBeginOverlap.RemoveDynamic(this, &ALavaStep::OnDamageBoxBeginOverlap);
    MonsterActivateCollision->OnComponentBeginOverlap.RemoveDynamic(this, &ALavaStep::OnMonsterBoxBeginOverlap);
    for (AActor* obj : ActorsToHide)
    {
        if (obj)
        {
            obj->SetActorHiddenInGame(true);
            obj->SetActorTickEnabled(false);
            obj->SetActorEnableCollision(false);
        }
    }

    OnStepCompleted.Broadcast();
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
    if (Monster) {
        Monster->Deactivate();
    }
   
}

void ALavaStep::OnDamageBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    EndStep();
}

void ALavaStep::OnCompletionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    EndStep();
}

void ALavaStep::OnMonsterBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!Monster) {
        return;
    }

    Monster->Activate();
    Monster->SetActorLocation(MonsterStartPosition->GetComponentLocation());
    Monster->SetTargetSpeed(100);
    Monster->SetTargetVector(PlayerPawn->GetActorLocation());
    Monster->StartMovement();
    
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        this,
        &ALavaStep::SetMonsterMoveDirection,
        0.4f,
        true
    );
}

void ALavaStep::SetMonsterMoveDirection()
{
    Monster->SetTargetVector(PlayerPawn->GetActorLocation());
}
