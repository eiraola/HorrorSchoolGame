// Fill out your copyright notice in the Description page of Project Settings.


#include "LookAtStep.h"
#include "Kismet/GameplayStatics.h"
#include "../HorrorSchoolCharacter.h"
#include "Components/SceneComponent.h"
// Sets default values
ALookAtStep::ALookAtStep()
{
	PrimaryActorTick.bCanEverTick = false;
	RootElement = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = RootElement;
	LookAtPosition = CreateDefaultSubobject<USceneComponent>("LookAt");
	StayInPosition = CreateDefaultSubobject<USceneComponent>("StayIn");
	StayInPosition->SetupAttachment(RootComponent);
	LookAtPosition->SetupAttachment(RootComponent);
	CurrentTimeToPass = 0.0f;
	TimeToPassStep = 10.0f;
	DistanceToLookAt = 3.0f;
	RotationToLookAt = 20.0f;
}

// Called when the game starts or when spawned
void ALookAtStep::BeginPlay()
{
	Super::BeginPlay();
	PlayerActor = Cast<AHorrorSchoolCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	CurrentTimeToPass = 0.0f;
	
}

void ALookAtStep::LookingAt()
{
	if (!PlayerActor) {
		return;
	}
	if ((PlayerActor->GetActorLocation() - StayInPosition->GetComponentLocation()).Size() > DistanceToLookAt) {
		CurrentTimeToPass = 0.0f;
		return;
	}
	
	FVector CameraPos;
	FRotator CameraRot;
	PlayerActor->GetController()->GetPlayerViewPoint(CameraPos, CameraRot);
	FVector DirectionToTarget = (LookAtPosition->GetComponentLocation() - CameraPos).GetSafeNormal();
	float DotProduct = FVector::DotProduct(CameraRot.Vector(), DirectionToTarget);

	float AngleRadians = FMath::Acos(DotProduct);
	float AngleDegrees = FMath::RadiansToDegrees(AngleRadians);

	if (AngleDegrees > RotationToLookAt) {
		CurrentTimeToPass = 0.0f;
		return;
	}
	CurrentTimeToPass += 0.02f;

	if (CurrentTimeToPass >= TimeToPassStep) {
		EndStep();
	}
}

void ALookAtStep::StartStep()
{
	LoadObjects();
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&ALookAtStep::LookingAt,
		0.02f,
		true
	);
}

void ALookAtStep::EndStep()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	UnloadObjects();
	OnStepCompleted.Broadcast();
}

void ALookAtStep::LoadObjects()
{
	for (AActor* actor : ActorsToActivate) {
		actor->SetActorHiddenInGame(false);
	}
}

void ALookAtStep::UnloadObjects()
{

	for (AActor* actor : ActorsToActivate) {
		actor->SetActorHiddenInGame(true);
	}
}

