// Fill out your copyright notice in the Description page of Project Settings.


#include "TelephoneInteractable.h"

// Sets default values
ATelephoneInteractable::ATelephoneInteractable()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ATelephoneInteractable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATelephoneInteractable::Interact()
{
	UE_LOG(LogTemp, Warning, TEXT("WOPS!!!!"));
}

void ATelephoneInteractable::Activate()
{
}

void ATelephoneInteractable::Deactivate()
{
}



