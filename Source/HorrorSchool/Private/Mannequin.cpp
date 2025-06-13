// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
AMannequin::AMannequin()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootElement = CreateDefaultSubobject<USceneComponent>(TEXT("RootElement"));
	RootComponent = RootElement;

	FirstPosition = CreateDefaultSubobject<USceneComponent>(TEXT("First Position"));
	FirstPosition->SetupAttachment(RootComponent);

	SecondPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Second Position"));
	SecondPosition->SetupAttachment(RootComponent);

	ThirdPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Third Position"));
	ThirdPosition->SetupAttachment(RootComponent);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	InitialPos = Mesh->GetRelativeLocation();
	InitialRotation = Mesh->GetRelativeRotation();
	
}

void AMannequin::SetNextPosition()
{
}

void AMannequin::SetFirstPosition()
{
	Mesh->SetRelativeLocation(FirstPosition->GetRelativeLocation());
	Mesh->SetRelativeRotation(FirstPosition->GetRelativeRotation());
}

void AMannequin::SetSecondPosition()
{
	Mesh->SetRelativeLocation(SecondPosition->GetRelativeLocation());
	Mesh->SetRelativeRotation(SecondPosition->GetRelativeRotation());
}

void AMannequin::SetThirdPosition()
{
	Mesh->SetRelativeLocation(ThirdPosition->GetRelativeLocation());
	Mesh->SetRelativeRotation(ThirdPosition->GetRelativeRotation());
}

void AMannequin::Activate()
{
	Mesh->SetHiddenInGame(false);
	SetActorLocation(InitialPos);
	SetActorRotation(InitialRotation);
	Mesh->SetRelativeLocation(InitialPos);
	Mesh->SetRelativeRotation(InitialRotation);
}

void AMannequin::Deactivate()
{
	Mesh->SetHiddenInGame(true);
}


