// Fill out your copyright notice in the Description page of Project Settings.


#include "AnomalySelector.h"
#include "Anomaly.h"
#include"Engine/Engine.h"
// Sets default values
AAnomalySelector::AAnomalySelector()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentAnomaly = nullptr;
	CurrentAnomalyIndex = 0;
}

// Called when the game starts or when spawned
void AAnomalySelector::BeginPlay()
{
	Super::BeginPlay();
	StartAnomaly();
	
}



void AAnomalySelector::StartAnomaly()
{
	if (Anomalies.IsValidIndex(CurrentAnomalyIndex)) {
		CurrentAnomaly = Anomalies[CurrentAnomalyIndex];
		CurrentAnomaly->StartAnomaly();
		CurrentAnomaly->OnAnomalyCompleted.AddDynamic(this, &AAnomalySelector::FinishAnomaly);
	}
	//If not, the game finishes;
}

void AAnomalySelector::SelectAnomaly()
{
	CurrentAnomalyIndex++;
	StartAnomaly();
}

void AAnomalySelector::FinishAnomaly()
{
	UE_LOG(LogTemp, Warning, TEXT("Opening door"));
	CurrentAnomaly->OnAnomalyCompleted.RemoveDynamic(this, &AAnomalySelector::FinishAnomaly);
	OnAnomalyFinished.Broadcast();
}

void AAnomalySelector::CancelCurrentAnomaly()
{
	if (!CurrentAnomaly) {
		return;
	}

	CurrentAnomaly->CancelAnomaly();
	CurrentAnomalyIndex = 0;
	OnAnomalyCanceled.Broadcast();
}



