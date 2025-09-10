// Fill out your copyright notice in the Description page of Project Settings.


#include "Steps/PushButtonsStep.h"
#include "InteractableElements/InteractableButton.h"
#include "Kismet/GameplayStatics.h"
#include "../HorrorSchoolCharacter.h"

APushButtonsStep::APushButtonsStep()
{
	CurrentIndex = 0;
}

void APushButtonsStep::BeginPlay()
{
	BlueButton.Get()->OnInteractionFinished.AddDynamic(this, &APushButtonsStep::OnBlueButtonPressed);
	RedButton.Get()->OnInteractionFinished.AddDynamic(this, &APushButtonsStep::OnRedButtonPressed);
	YellowButton.Get()->OnInteractionFinished.AddDynamic(this, &APushButtonsStep::OnYellowButtonPressed);
	GreenButton.Get()->OnInteractionFinished.AddDynamic(this, &APushButtonsStep::OnGreenButtonPressed);
}

void APushButtonsStep::StartStep()
{
	ResetButons();
	PlayerCharacter = Cast<AHorrorSchoolCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (!PlayerCharacter) {
		return;
	}

	PlayerCharacter->StartLookingInteractables();
}

void APushButtonsStep::EndStep()
{
	PlayerCharacter->StopLookingInteractables();
	ResetButons();
	CurrentIndex = 0;
	OnStepCompleted.Broadcast();
}

void APushButtonsStep::OnRedButtonPressed()
{
	if (CurrentIndex != 3) {
		ResetButons();
		CurrentIndex = 0;
		return;
	}
	EndStep();
}

void APushButtonsStep::OnYellowButtonPressed()
{
	if (CurrentIndex != 0) {
		ResetButons();
		CurrentIndex = 0;
		return;
	}
	CurrentIndex++;
}

void APushButtonsStep::OnBlueButtonPressed()
{
	if (CurrentIndex != 1) {
		ResetButons();
		CurrentIndex = 0;
		return;
	}
	CurrentIndex++;
}

void APushButtonsStep::OnGreenButtonPressed()
{
	if (CurrentIndex != 2) {
		ResetButons();
		CurrentIndex = 0;
		return;
	}
	CurrentIndex++;
}

void APushButtonsStep::ResetButons()
{
	CurrentIndex = 0;
	BlueButton.Get()->RestartButton();
	YellowButton.Get()->RestartButton();
	RedButton.Get()->RestartButton();
	GreenButton.Get()->RestartButton();
}
