// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableElements/InteractableButton.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
void AInteractableButton::BeginPlay()
{
	DynamicMaterial = ButtonMesh->CreateAndSetMaterialInstanceDynamic(0);

	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("No se pudo crear el MID en ButtonMesh slot 0"));
		return;
	}
	RestartButton();
	// Opcional: verifica nº de materiales y loggea
	UE_LOG(LogTemp, Log, TEXT("Num materiales: %d"), ButtonMesh->GetNumMaterials());
	
}
AInteractableButton::AInteractableButton()
{
	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;
	Collision = CreateDefaultSubobject<UBoxComponent>("CollisionComponent");
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	ButtonMesh = CreateDefaultSubobject<UStaticMeshComponent>("ButtonMesh");
	ButtonMesh->SetupAttachment(RootComponent);
}

void AInteractableButton::Interact()
{
	if (IsUsed) {
		return;
	}
	Use();
	OnInteractionFinished.Broadcast();
	
}

void AInteractableButton::Activate()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	Collision->SetCollisionResponseToAllChannels(ECR_Block);
	SetActorHiddenInGame(false);
}

void AInteractableButton::Deactivate()
{
	Collision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Collision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetActorHiddenInGame(true);
}


void AInteractableButton::RestartButton()
{
	if (!DynamicMaterial) {
		if (ButtonMesh) {
			DynamicMaterial = UMaterialInstanceDynamic::Create(ButtonMesh->GetMaterial(0), this);
		}
		if (DynamicMaterial)
		{
			ButtonMesh->SetMaterial(0, DynamicMaterial);
		}
	}
	if (!DynamicMaterial)
	{
		UE_LOG(LogTemp, Warning, TEXT("No hay materrial"));
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("Hay Material"));
	DynamicMaterial->SetScalarParameterValue(TEXT("Emission"), 1.0f);
	IsUsed = false;
}

void AInteractableButton::Use()
{
	DynamicMaterial->SetScalarParameterValue(TEXT("Emission"), 0.0f);
	IsUsed = true;
}
