// Fill out your copyright notice in the Description page of Project Settings.


#include "Steps/InteractWithObjectStep.h"
#include "../HorrorSchoolCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractWithObjectStep::AInteractWithObjectStep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
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
	
}

void AInteractWithObjectStep::EndStep()
{
}



