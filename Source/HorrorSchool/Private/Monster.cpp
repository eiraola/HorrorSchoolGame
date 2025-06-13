// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

#include "Engine/Engine.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TargetSpeed = 0;
	TargetPosition = FVector::ZeroVector;
	bIsMoving = false;

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsMoving) {
		return;
	}

	
	FVector targetDirection = (TargetPosition - GetActorLocation());
	float currentDistance = targetDirection.Size();
	if (currentDistance <= DeltaTime * TargetSpeed) {
		SetActorLocation(TargetPosition);
		StopMovement();
		return;
	}
	targetDirection.Normalize();
	targetDirection = targetDirection * DeltaTime * TargetSpeed;
	SetActorLocation(GetActorLocation() + targetDirection);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMonster::SetTargetVector(FVector targetPosition)
{
	TargetPosition = targetPosition;
}

void AMonster::StartMovement()
{
	bIsMoving = true;
}

void AMonster::StopMovement()
{

	OnPositionReached.Broadcast();
	bIsMoving = false;
}

void AMonster::SetTargetSpeed(float targetSpeed)
{
	TargetSpeed = targetSpeed;
}

void AMonster::Activate()
{
	SetActorTickEnabled(true);
	SetActorHiddenInGame(false);
}

void AMonster::Deactivate()
{
	SetActorTickEnabled(false);
	SetActorHiddenInGame(true);
	SetActorLocation(FVector::ZeroVector);
	bIsMoving = false;
}

