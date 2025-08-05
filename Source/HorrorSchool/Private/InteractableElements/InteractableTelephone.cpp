// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableElements/InteractableTelephone.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"

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
	
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_Visibility);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
}

// Called when the game starts or when spawned
void AInteractableTelephone::BeginPlay()
{
	Super::BeginPlay();
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

void AInteractableTelephone::Interact()
{
	OnInteractionFinished.Broadcast();
}

void AInteractableTelephone::Activate()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SetActorHiddenInGame(false);
}

void AInteractableTelephone::Deactivate()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetActorHiddenInGame(true);
}



