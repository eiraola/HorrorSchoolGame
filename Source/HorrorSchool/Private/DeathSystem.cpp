// Fill out your copyright notice in the Description page of Project Settings.



#include "DeathSystem.h"
#include "../HorrorSchoolCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "AnomalySelector.h"
// Sets default values
ADeathSystem::ADeathSystem()
{
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADeathSystem::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = Cast<AHorrorSchoolCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (PlayerCharacter) {
		PlayerCharacter->OnPlayerDead.AddDynamic(this, &ADeathSystem::OnPlayerDead);
	}
	
}

// Called every frame
void ADeathSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADeathSystem::OnPlayerDead()
{
	if (!AnomalySelector) {
		return;
	}

	AnomalySelector->CancelCurrentAnomaly();
}

