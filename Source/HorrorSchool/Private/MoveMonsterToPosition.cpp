// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveMonsterToPosition.h"
#include "Monster.h"
#include "Components/SceneComponent.h"
// Sets default values
 AMoveMonsterToPositionStep::AMoveMonsterToPositionStep()
{
	PrimaryActorTick.bCanEverTick = false;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	StartPosition = CreateDefaultSubobject<USceneComponent>(TEXT("StartPosition"));
	StartPosition->SetupAttachment(RootComponent);
	EndPosition = CreateDefaultSubobject<USceneComponent>(TEXT("EndPosition"));
	EndPosition->SetupAttachment(RootComponent);
	bShouldHideEnemyOnFinish = 1;
}

// Called when the game starts or when spawned
void AMoveMonsterToPositionStep::BeginPlay()
{
	Super::BeginPlay();
}

void AMoveMonsterToPositionStep::StartStep()
{
	if (!Monster) {
		EndStep();
		return;
	}

	Monster->Activate();
	Monster->SetTargetSpeed(300);
	Monster->SetActorLocation(StartPosition->GetComponentLocation());
	Monster->SetTargetVector(EndPosition->GetComponentLocation());
	Monster->OnPositionReached.AddDynamic(this, &AMoveMonsterToPositionStep::EndStep);
	Monster->StartMovement();
}

void AMoveMonsterToPositionStep::EndStep()
{
	UE_LOG(LogTemp, Warning, TEXT("StepFinalizado"));
	if (!Monster) {
		OnStepCompleted.Broadcast();
		return;
	}

	Monster->OnPositionReached.RemoveDynamic(this, &AMoveMonsterToPositionStep::EndStep);
	Monster->StopMovement();
	if (bShouldHideEnemyOnFinish) {
		Monster->Deactivate();
	}
	OnStepCompleted.Broadcast();
}


