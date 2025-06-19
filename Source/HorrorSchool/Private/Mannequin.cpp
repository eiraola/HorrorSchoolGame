// Fill out your copyright notice in the Description page of Project Settings.


#include "Mannequin.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneCaptureComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "../HorrorSchoolCharacter.h"
#include "Engine/Engine.h"

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

	EnemyCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collider"));
	EnemyCollider->SetupAttachment(Mesh);
	EnemyCollider->SetCollisionObjectType(ECC_WorldDynamic);
	EnemyCollider->SetCollisionResponseToAllChannels(ECR_Ignore);
	EnemyCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	EnemyCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	EnemyCollider->SetGenerateOverlapEvents(true);

}

// Called when the game starts or when spawned
void AMannequin::BeginPlay()
{
	Super::BeginPlay();
	InitialPos = Mesh->GetRelativeLocation();
	InitialRotation = Mesh->GetRelativeRotation();
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("¡AMannequin creado!"));
	}
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
	SetActorHiddenInGame(false);
	Mesh->SetHiddenInGame(false);
	Mesh->SetRelativeLocation(InitialPos);
	Mesh->SetRelativeRotation(InitialRotation);
	EnemyCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	EnemyCollider->OnComponentBeginOverlap.AddDynamic(this, &AMannequin::OnCapsuleBeginOverlap);
	UE_LOG(LogTemp, Warning, TEXT("Hay Collision"))
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("ZDDD"));
		}
}

void AMannequin::Deactivate()
{
	SetActorHiddenInGame(true);
	Mesh->SetHiddenInGame(true);
	EnemyCollider->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	EnemyCollider->OnComponentBeginOverlap.RemoveDynamic(this, &AMannequin::OnCapsuleBeginOverlap);
}

void AMannequin::OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Hay Collision"));
	if (!OtherActor) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Hay Actor"));
	AHorrorSchoolCharacter* PlayerCharacter = Cast<AHorrorSchoolCharacter>(OtherActor);

	if (!PlayerCharacter) {
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Hay Player"));
	PlayerCharacter->KillPlayer();
}


