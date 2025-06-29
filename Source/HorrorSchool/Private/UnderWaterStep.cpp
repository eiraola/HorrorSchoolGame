// Fill out your copyright notice in the Description page of Project Settings.


#include "UnderWaterStep.h"
#include "Components/BoxComponent.h"
#include "../HorrorSchoolCharacter.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
// Sets default values
AUnderWaterStep::AUnderWaterStep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootElement = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootElement;

	StartCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("StartCollider"));
	StartCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	StartCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StartCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	StartCollider->SetupAttachment(RootComponent);

	EndCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("EndCollider"));
	EndCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	EndCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EndCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	EndCollider->SetupAttachment(RootComponent);
	WaterSpeed = 1.0f;
}

// Called when the game starts or when spawned
void AUnderWaterStep::BeginPlay()
{
	Super::BeginPlay();
	PlayerCharacter = Cast<AHorrorSchoolCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
}

void AUnderWaterStep::OnStartColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	PlayerCharacter->SetWetStepSound();
	WaterActor->SetActorHiddenInGame(false);
	GetWorld()->GetTimerManager().SetTimer(
		WaterMovementTimer,
		this,
		&AUnderWaterStep::MoveWater,
		0.02f,
		true
	);

	GetWorld()->GetTimerManager().SetTimer(
		PlayerKillerTimer,
		this,
		&AUnderWaterStep::KillPlayer,
		15.2f,
		false
	);
}

void AUnderWaterStep::OnEndColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	EndStep();
}

void AUnderWaterStep::KillPlayer()
{
	PlayerCharacter->KillPlayer();
}

void AUnderWaterStep::MoveWater()
{
	FVector TargetDirection = WaterEndLocation - WaterStartLocation;
	TargetDirection.Normalize();
	WaterActor->SetActorLocation(WaterActor->GetActorLocation() + TargetDirection.Normalize() * 0.02f * WaterSpeed);
}

// Called every frame
void AUnderWaterStep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnderWaterStep::StartStep()
{
	StartCollider->OnComponentBeginOverlap.AddDynamic(this, &AUnderWaterStep::OnStartColliderBeginOverlap);
	StartCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	StartCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	EndCollider->OnComponentBeginOverlap.AddDynamic(this, &AUnderWaterStep::OnEndColliderBeginOverlap);
	EndCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EndCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	WaterActor->SetActorLocation(WaterStartLocation);

	
}

void AUnderWaterStep::EndStep()
{
	PlayerCharacter->SetStepSound();
	StartCollider->OnComponentBeginOverlap.RemoveDynamic(this, &AUnderWaterStep::OnStartColliderBeginOverlap);
	StartCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	StartCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	EndCollider->OnComponentBeginOverlap.RemoveDynamic(this, &AUnderWaterStep::OnEndColliderBeginOverlap);
	EndCollider->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EndCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	WaterActor->SetActorHiddenInGame(true);
	GetWorld()->GetTimerManager().ClearTimer(PlayerKillerTimer);
	GetWorld()->GetTimerManager().ClearTimer(WaterMovementTimer);
	WaterActor->SetActorLocation(WaterStartLocation);
	OnStepCompleted.Broadcast();
}

