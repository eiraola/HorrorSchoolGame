// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyStep.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Monster.h"


// Sets default values
AEnemyStep::AEnemyStep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RootPoint"));
	RootComponent = RootPoint;
	EncounterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EncounterCollision"));
	EncounterCollision->SetupAttachment(RootComponent);
	EncounterCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EncounterCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	EncounterCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RunCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("RunCollision"));
	RunCollision->SetupAttachment(RootComponent);
	RunCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RunCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	RunCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	StartingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("StartingPoint"));
	StartingPoint->SetupAttachment(RootComponent);
	EndingPoint = CreateDefaultSubobject<USceneComponent>(TEXT("EndingPoint"));
	EndingPoint->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void AEnemyStep::BeginPlay()
{
	Super::BeginPlay();
	if (EnemyMonster) {
		EnemyMonster->SetActorLocation(StartingPoint->GetComponentLocation());
		EnemyMonster->SetTargetVector(EndingPoint->GetComponentLocation());
		EnemyMonster->SetTargetSpeed(1000);
	}
	EncounterCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyStep::OnEncounterCollisionBeginOverlap);
	RunCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyStep::OnRunCollisionBeginOverlap);
}

// Called every frame
void AEnemyStep::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyStep::StartStep()
{
	EnemyMonster->Activate();
	EncounterCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	RunCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

void AEnemyStep::EndStep()
{
	EnemyMonster->OnPositionReached.RemoveDynamic(this, &AEnemyStep::EndStep);
	EnemyMonster->Deactivate();
	EncounterCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RunCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	OnStepCompleted.Broadcast();
	UE_LOG(LogTemp, Warning, TEXT("Step finished"));
}

void AEnemyStep::OnEncounterCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	EnemyMonster->StartMovement();
}

void AEnemyStep::OnRunCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	EnemyMonster->OnPositionReached.AddDynamic(this, &AEnemyStep::EndStep);
	EnemyMonster->SetTargetVector(StartingPoint->GetComponentLocation());
	EnemyMonster->StartMovement();
}

