// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTeleporter.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/PostProcessVolume.h"
#include "PostProcessController.h"
// Sets default values
APlayerTeleporter::APlayerTeleporter()
{

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));
	AppearVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("AppearanceVolume"));
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    TriggerVolume->SetGenerateOverlapEvents(true);
    SetActorEnableCollision(true);
	TriggerVolume->SetupAttachment(RootComponent);
	AppearVolume->SetupAttachment(RootComponent);
    TriggerVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    TriggerVolume->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
    TriggerVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
    TriggerVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

// Called when the game starts or when spawned
void APlayerTeleporter::BeginPlay()
{
	Super::BeginPlay();
    TriggerVolume->OnComponentBeginOverlap.AddDynamic(this ,&APlayerTeleporter::onVolumeBeginOverlap);
}

void APlayerTeleporter::onVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (TeleportGlitchSound)
    {
        UGameplayStatics::PlaySoundAtLocation(this, TeleportGlitchSound, GetActorLocation());
    }
    TeleportableActor = OtherActor;
    DoGlitchAnimation();
    GetWorld()->GetTimerManager().SetTimer(
        TimerHandle,
        this,
        &APlayerTeleporter::DoTeleport,
        0.3f,
        false
    );
}

void APlayerTeleporter::DoTeleport()
{
    FTransform TriggerTransform = TriggerVolume->GetComponentTransform();
    FTransform AppearTransform = AppearVolume->GetComponentTransform();

    FTransform ActorLocalTransform = TeleportableActor->GetActorTransform().GetRelativeTransform(TriggerTransform);
    FTransform TargetWorldTransform = ActorLocalTransform * AppearTransform;


    TeleportableActor->SetActorLocationAndRotation(
        TargetWorldTransform.GetLocation(),
        TargetWorldTransform.GetRotation().Rotator()
    );
    FRotator TargetRotation = TargetWorldTransform.GetRotation().Rotator();

    APawn* Pawn = Cast<APawn>(TeleportableActor);
    if (Pawn && Pawn->IsPlayerControlled())
    {
        AController* Controller = Pawn->GetController();
        if (Controller)
        {
            Controller->SetControlRotation(TargetRotation);
        }
    }

    TeleportableActor->SetActorRotation(TargetRotation);
    OnLoopFinished.Broadcast();
}

