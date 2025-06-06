// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DoorStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("DoorMesh");
	HolderStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("HolderMesh");
	RootComponent = HolderStaticMesh;
	DoorStaticMesh->SetupAttachment(RootComponent);
	DoorEndPositionGizmo = CreateDefaultSubobject<USceneComponent>("EndPositionGizmo");
	DoorEndPositionGizmo->SetupAttachment(RootComponent);
	DoorBeginPositionGizmo = CreateDefaultSubobject<USceneComponent>("EndBeginGizmo");
	DoorBeginPositionGizmo->SetupAttachment(RootComponent);
	DoorCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorCollision"));
	DoorCollision->SetupAttachment(RootComponent);
	DoorCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	DoorCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent);
	CollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionBox->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	CollisionBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionBox->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	bIsReseted = true;
}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnBoxBeginOverlap);
	
}

void ADoorActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsReseted) {
		return;
	}

	if (!OtherActor) {
		return;
	}
	if (OpenDoorSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, OpenDoorSound, GetActorLocation());
	}
	bIsReseted = false;
	CloseDoor();
}

void ADoorActor::ResetDoor()
{
	bIsReseted = true;
}

void ADoorActor::EnableDoorCollisions()
{
	DoorCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
}

void ADoorActor::DisableDoorCollisions()
{
	DoorCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}




