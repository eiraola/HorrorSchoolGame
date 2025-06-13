// Fill out your copyright notice in the Description page of Project Settings.


#include "GreenLightStep.h"
#include "TimerManager.h"
#include "LightsManager.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Monster.h"
// Sets default values
AGreenLightStep::AGreenLightStep()
{
	PrimaryActorTick.bCanEverTick = false;
    SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = SceneRoot;
    CompletionCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("FinishCollision"));
    CompletionCollision->SetupAttachment(RootComponent);
    RedColor = FLinearColor(1, 0, 0);
    CompletionCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CompletionCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    CompletionCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    MonsterPositionGizmo = CreateDefaultSubobject<USceneComponent>(TEXT("MonsterPosition"));
    MonsterPositionGizmo->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AGreenLightStep::BeginPlay()
{
	Super::BeginPlay();
}

void AGreenLightStep::SwapLightColor()
{
    if (!LightsManager) {
        return;
    }

    if (CurrentColor == 0) {
        LightsManager->ChangeLightsColor(FLinearColor(1, 0, 0));
    }

    if (CurrentColor == 1) {
        LightsManager->ResetLights();
    }

    CurrentColor++;
    if (CurrentColor > 1) {
        CurrentColor = 0;
    }

    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        this,
        &AGreenLightStep::SwapLightColor,
        FMath::RandRange(2, 4),
        false
    );
}

void AGreenLightStep::StartStep()
{
    if (Monster)
    {
        Monster->Activate();
        Monster->SetActorLocation(MonsterPositionGizmo->GetComponentLocation());
        Monster->SetActorRotation(MonsterPositionGizmo->GetComponentRotation());
    }
    CompletionCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
    CompletionCollision->OnComponentBeginOverlap.AddDynamic(this, &AGreenLightStep::OnCompletionCollisionBeginOverlap);
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        this,
        &AGreenLightStep::SwapLightColor,
        FMath::RandRange(2, 4),
        false
    );
}

void AGreenLightStep::EndStep()
{
    if (Monster)
    {
        Monster->Deactivate();
    }
    CompletionCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
    LightsManager->ResetLights();
    OnStepCompleted.Broadcast();

}

void AGreenLightStep::OnCompletionCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    EndStep();
}



