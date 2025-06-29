// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"

#include "Engine/Engine.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneComponent.h"
// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	TargetSpeed = 0;
	TargetPosition = FVector::ZeroVector;
	bIsMoving = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	REye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("REye"));
	LEye = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LEye"));
	RootComponent = Root;
	Body->SetupAttachment(RootComponent);

	REye->SetupAttachment(Body);
	LEye->SetupAttachment(Body);
	REye->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LEyeSocket"));
	LEye->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("REyeSocket"));

	
	

}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	if (Body->DoesSocketExist("LEyeSocket"))
	{
		REye->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("LEyeSocket"));
	}

	if (Body->DoesSocketExist("REyeSocket"))
	{
		LEye->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("REyeSocket"));
	}
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
	UE_LOG(LogTemp, Warning, TEXT("Paro"));
	
	bIsMoving = false;
	OnPositionReached.Broadcast();
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

