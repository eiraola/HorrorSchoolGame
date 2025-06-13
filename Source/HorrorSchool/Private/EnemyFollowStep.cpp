// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyFollowStep.h"
#include "Monster.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemyFollowStep::AEnemyFollowStep()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	RootElement = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootElement;

	EnemyEncounterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnemyEncounterCollision"));
	EnemyEncounterCollision->SetupAttachment(RootComponent);
	EnemyEncounterCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	EnemyEncounterCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	EnemyEncounterCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	StepEndCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("StepEndCollision"));
	StepEndCollision->SetupAttachment(RootComponent);
	StepEndCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	StepEndCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	StepEndCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	EnemyStartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyStartPosition"));
	EnemyStartPosition->SetupAttachment(RootComponent);

	EnemyReachPosition = CreateDefaultSubobject<USceneComponent>(TEXT("EnemyReachPosition"));
	EnemyReachPosition->SetupAttachment(RootComponent);

	bIsEnemyAwake = false;

}

// Called when the game starts or when spawned
void AEnemyFollowStep::BeginPlay()
{
	Super::BeginPlay();

	PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	
}

void AEnemyFollowStep::StartStep()
{
	EnemyEncounterCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyFollowStep::OnEnemyEncounterCollisionBeginOverlap);
	EnemyEncounterCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	StepEndCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyFollowStep::OnEndStepCollisionBeginOverlap);
	StepEndCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ObstacleObject->SetActorHiddenInGame(true);
	ObstacleObject->SetActorEnableCollision(false);
	bIsEnemyAwake = false;
}

void AEnemyFollowStep::EndStep()
{
	EnemyEncounterCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AEnemyFollowStep::OnEnemyEncounterCollisionBeginOverlap);
	EnemyEncounterCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	StepEndCollision->OnComponentBeginOverlap.RemoveDynamic(this, &AEnemyFollowStep::OnEndStepCollisionBeginOverlap);
	StepEndCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	ObstacleObject->SetActorHiddenInGame(false);
	ObstacleObject->SetActorEnableCollision(true);
}

void AEnemyFollowStep::SetMonsterDirection()
{
	if (!Monster || !PlayerPawn) {
		return;
	}

	Monster->SetTargetVector(PlayerPawn->GetActorLocation());
	Monster->StartMovement();
}

void AEnemyFollowStep::OnEnemyEncounterCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bIsEnemyAwake) {
		return;
	}

	bIsEnemyAwake = true;

	if (!Monster) {
		return;
	}
	Monster->SetActorLocation(EnemyStartPosition->GetComponentLocation());
	Monster->Activate();
	Monster->SetTargetSpeed(300);
	Monster->SetTargetVector(EnemyReachPosition->GetComponentLocation());
	Monster->OnPositionReached.AddDynamic(this, &AEnemyFollowStep::OnEnemyStairsReach);
	Monster->StartMovement();
}

void AEnemyFollowStep::OnEndStepCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bIsEnemyAwake) {
		return;
	}
	EndStep();
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	Monster->Deactivate();
	OnStepCompleted.Broadcast();
}

void AEnemyFollowStep::OnEnemyStairsReach()
{
	Monster->OnPositionReached.RemoveDynamic(this, &AEnemyFollowStep::OnEnemyStairsReach);
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&AEnemyFollowStep::SetMonsterDirection,
		0.2f,
		true
	);
	Monster->StartMovement();
}


