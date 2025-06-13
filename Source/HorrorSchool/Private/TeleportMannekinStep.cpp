// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleportMannekinStep.h"
#include "Components/BoxComponent.h"
#include "Components/BoxComponent.h"
#include "Mannequin.h"

// Sets default values
ATeleportMannekinStep::ATeleportMannekinStep()
{
	PrimaryActorTick.bCanEverTick = false;

	RootElement = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootElement;

	ManequinTeleportCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("MannequinCollider"));
	ManequinTeleportCollider->SetupAttachment(RootComponent);
	ManequinTeleportCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	ManequinTeleportCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	ManequinTeleportCollider->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

}


void ATeleportMannekinStep::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleportMannekinStep::StartStep()
{
	ManequinTeleportCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ManequinTeleportCollider->OnComponentBeginOverlap.AddDynamic(this, &ATeleportMannekinStep::OnManequinColliderBeginOverlap);

	if (TeleportNumber != ETeleportNumber::ET_First) {
		return;
	}
	for (AMannequin* Mannequin : MannequinsToActivate)
	{
		if (Mannequin)
		{
			Mannequin->SetActorHiddenInGame(false);
		}
	}
}

void ATeleportMannekinStep::EndStep()
{

	ManequinTeleportCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	ManequinTeleportCollider->OnComponentBeginOverlap.RemoveDynamic(this, &ATeleportMannekinStep::OnManequinColliderBeginOverlap);
	OnStepCompleted.Broadcast();

	if (TeleportNumber != ETeleportNumber::ET_None) {
		return;
	}

	for (AMannequin* Mannequin : MannequinsToActivate)
	{
		if (Mannequin)
		{
			Mannequin->SetActorHiddenInGame(true);
		}
	}
}

void ATeleportMannekinStep::OnManequinColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (AMannequin* Mannequin : Mannequins)
	{
		if (Mannequin)
		{
			if (TeleportNumber == ETeleportNumber::ET_First) {
				Mannequin->SetFirstPosition();
			}

			if (TeleportNumber == ETeleportNumber::ET_Second) {
				Mannequin->SetSecondPosition();
			}

			if (TeleportNumber == ETeleportNumber::ET_Third) {
				Mannequin->SetThirdPosition();
			}
		}
	}

	EndStep();
}


