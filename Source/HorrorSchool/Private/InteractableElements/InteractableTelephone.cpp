// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableElements/InteractableTelephone.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"

// Sets default values
AInteractableTelephone::AInteractableTelephone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Collision = CreateDefaultSubobject<UBoxComponent>(TEXT("Collision"));
	Collision->SetupAttachment(RootComponent);
	
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	AudioComp = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComp"));
	AudioComp->bAutoActivate = false;
	AudioComp->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractableTelephone::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableTelephone::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("El Interactable interactua"));

	if (TakePhoneSound) {
		AudioComp->SetSound(TakePhoneSound);
		AudioComp->Play(0.f);
	}

	OnInteractionFinished.Broadcast();
}

void AInteractableTelephone::Activate()
{
	UE_LOG(LogTemp, Warning, TEXT("Se activa"));
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);

	if (RingSound) {
		AudioComp->SetSound(RingSound);
		AudioComp->Play(0.f);
	}
	
	SetActorHiddenInGame(false);
}

void AInteractableTelephone::Deactivate()
{

	UE_LOG(LogTemp, Warning, TEXT("Se des"));
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetActorHiddenInGame(true);
}



