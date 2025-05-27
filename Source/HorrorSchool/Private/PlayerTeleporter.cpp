// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerTeleporter.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Engine/Engine.h"
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
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("¡Hola desde C++!"));
    }
	
}

void APlayerTeleporter::onVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    UE_LOG(LogTemp, Warning, TEXT("Actor %s ha entrado al volumen"), *OtherActor->GetName());
    // Obtener la posición y rotación relativa al TriggerVolume
    FTransform TriggerTransform = TriggerVolume->GetComponentTransform();
    FTransform AppearTransform = AppearVolume->GetComponentTransform();

    FTransform ActorLocalTransform = OtherActor->GetActorTransform().GetRelativeTransform(TriggerTransform);

    // Convertir esa posición y rotación al espacio del AppearVolume
    FTransform TargetWorldTransform = ActorLocalTransform * AppearTransform;

    // Teletransportar al actor
    OtherActor->SetActorLocationAndRotation(
        TargetWorldTransform.GetLocation(),
        TargetWorldTransform.GetRotation().Rotator()
    );
    FRotator TargetRotation = TargetWorldTransform.GetRotation().Rotator();
    // Si es el jugador, cambia la rotación del controlador

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (Pawn && Pawn->IsPlayerControlled())
    {
        AController* Controller = Pawn->GetController();
        if (Controller)
        {
            Controller->SetControlRotation(TargetRotation);
        }
    }

    // Asegúrate también de rotar el cuerpo del actor por coherencia
    OtherActor->SetActorRotation(TargetRotation);
    OnLoopFinished.Broadcast();
}

