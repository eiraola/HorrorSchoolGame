// Fill out your copyright notice in the Description page of Project Settings.


#include "Anomaly.h"
#include "Step.h"
#include "Kismet/GameplayStatics.h"
#include "PostProcessController.h"
// Sets default values
AAnomaly::AAnomaly()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CurrentStep = nullptr;

}

// Called when the game starts or when spawned
void AAnomaly::BeginPlay()
{
	Super::BeginPlay();
	CurrentStepIndex = 0;
	if (Steps.IsValidIndex(CurrentStepIndex))
	{
		CurrentStep = Steps[CurrentStepIndex];
	}
	
}

AStep* AAnomaly::GetNextStep()
{
	CurrentStepIndex++;
	if (Steps.IsValidIndex(CurrentStepIndex))
	{
		return Steps[CurrentStepIndex];
	}
	return nullptr;
}

void AAnomaly::ResetAnomaly()
{
	CurrentStepIndex = 0;
	CurrentStep = Steps[CurrentStepIndex];
}

void AAnomaly::StepCompleted()
{
	CurrentStep->OnStepCompleted.RemoveDynamic(this, &AAnomaly::StepCompleted);
	CurrentStep = GetNextStep();

	if (!CurrentStep) {
		CompleteAnomaly();
		return;
	}

	CurrentStep->StartStep();
	CurrentStep->OnStepCompleted.AddDynamic(this, &AAnomaly::StepCompleted);
}

void AAnomaly::StartAnomaly()
{
	CurrentStepIndex = 0;
	CurrentStep = Steps[CurrentStepIndex];
	CurrentStep->OnStepCompleted.AddDynamic(this, &AAnomaly::StepCompleted);
	CurrentStep->StartStep();
}

void AAnomaly::CancelAnomaly()
{
	if (CurrentStep) {
		CurrentStep->OnStepCompleted.RemoveDynamic(this, &AAnomaly::StepCompleted);
	}
	for (AStep* Step: Steps)
	{
		Step->EndStep();
	}
}

void AAnomaly::CompleteAnomaly()
{
	if (GlitchSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, GlitchSound, GetActorLocation());
	}
	if (PostProcessControler) {
		PostProcessControler->PlayDistorsionEffect();
	}
	ResetAnomaly();
	UE_LOG(LogTemp, Warning, TEXT("AnomalyFinished"));
	OnAnomalyCompleted.Broadcast();

}


