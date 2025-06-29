// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerFollowerMonsterStep.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "Monster.h"
#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"


// Sets default values
APlayerFollowerMonsterStep::APlayerFollowerMonsterStep()
{
	PrimaryActorTick.bCanEverTick = false;
	MonsterSpeed = 300;
	bDeactivateMonsterOnEnd = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	EndCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EndCollision"));
	EndCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EndCollision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	EndCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	EndCollision->SetupAttachment(RootComponent);
}

void APlayerFollowerMonsterStep::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacter = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
}

void APlayerFollowerMonsterStep::StartStep()
{
	if (!Monster) {
		EndStep();
	}
	EndCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EndCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	EndCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerFollowerMonsterStep::OnColliderBeginOverlap);
	Monster->Activate();
	Monster->SetTargetSpeed(MonsterSpeed);
	Monster->SetTargetVector(PlayerCharacter->GetActorLocation());
	Monster->StartMovement();
	GetWorld()->GetTimerManager().SetTimer(
		TimerHandle,
		this,
		&APlayerFollowerMonsterStep::ChasePlayer,
		0.1,
		true
	);
}

void APlayerFollowerMonsterStep::EndStep()
{
	EndCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	EndCollision->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Ignore);
	EndCollision->OnComponentBeginOverlap.RemoveDynamic(this, &APlayerFollowerMonsterStep::OnColliderBeginOverlap);
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
	if(bDeactivateMonsterOnEnd){
		Monster->Deactivate();
	}

	OnStepCompleted.Broadcast();
}

void APlayerFollowerMonsterStep::ChasePlayer()
{
	Monster->StartMovement();
	Monster->SetTargetVector(PlayerCharacter->GetActorLocation());
}

void APlayerFollowerMonsterStep::OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	EndStep();
}


