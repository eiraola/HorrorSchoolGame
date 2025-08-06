// Fill out your copyright notice in the Description page of Project Settings.


#include "Steps/InteractWithObjectStep.h"
#include "../HorrorSchoolCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Interactable.h"

// Sets default values
AInteractWithObjectStep::AInteractWithObjectStep()
{
	PrimaryActorTick.bCanEverTick = false;

}

void AInteractWithObjectStep::BeginPlay()
{
	Super::BeginPlay();
}

void AInteractWithObjectStep::StartStep()
{
	PlayerCharacter = Cast<AHorrorSchoolCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerCharacter) {
		return;
	}

	PlayerCharacter->StartLookingInteractables();

	if (!InteractableObject) {
		return;
	}

	InteractableObject->OnInteractionFinished.AddDynamic(this, &AInteractWithObjectStep::EndStep);
	
}

void AInteractWithObjectStep::EndStep()
{
	if (!InteractableObject) {
		return;
	}

	InteractableObject->OnInteractionFinished.RemoveDynamic(this, &AInteractWithObjectStep::EndStep);

	OnStepCompleted.Broadcast();
}



