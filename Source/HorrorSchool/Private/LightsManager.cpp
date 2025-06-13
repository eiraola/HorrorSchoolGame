// Fill out your copyright notice in the Description page of Project Settings.


#include "LightsManager.h"
#include "LightContainer.h"
#include "LightActor.h"
// Sets default values
ALightsManager::ALightsManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ALightsManager::BeginPlay()
{
	Super::BeginPlay();
    if (PointLightComponents.IsValidIndex(0)) {
        InitialColor = PointLightComponents[0]->GetLightColor();
    }
	
}

void ALightsManager::ChangeLightsColor(FLinearColor newColor)
{
    for (ALightActor* Light : PointLightComponents)
    {
        if (Light)
        {
            Light->SetLightColor(newColor);
        }
    }
}

void ALightsManager::ResetLights()
{
    ChangeLightsColor(InitialColor);
}

