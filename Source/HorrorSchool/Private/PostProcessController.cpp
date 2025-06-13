// Fill out your copyright notice in the Description page of Project Settings.


#include "PostProcessController.h"
#include "Engine/PostProcessVolume.h"

// Sets default values
APostProcessController::APostProcessController()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APostProcessController::BeginPlay()
{
	Super::BeginPlay();
    if (!PostProcessVolume)
    {
        return;
    }
       
    if (PostProcessVolume->Settings.WeightedBlendables.Array.Num() <= 0)
    {
        return;
    }
    FWeightedBlendable& Blendable = PostProcessVolume->Settings.WeightedBlendables.Array[0];

    UMaterialInterface* DynamicMaterial = Cast<UMaterialInterface>(Blendable.Object);
    if (!DynamicMaterial)
    {
        return;
    }

    DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Cast<UMaterialInterface>(DynamicMaterial), this);
    DynamicMaterialInstance->SetScalarParameterValue("Distorsion", 0.0f);

    FWeightedBlendable NewBlendable;
    NewBlendable.Object = DynamicMaterialInstance;
    NewBlendable.Weight = 1.0f;  

    
    PostProcessVolume->Settings.WeightedBlendables.Array.Empty();
    PostProcessVolume->Settings.WeightedBlendables.Array.Add(NewBlendable);
	
}

void APostProcessController::ChangeDistorsionValue(float newDistorsion)
{
    DynamicMaterialInstance->SetScalarParameterValue("Distorsion", newDistorsion);
}



