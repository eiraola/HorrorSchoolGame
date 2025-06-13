// Fill out your copyright notice in the Description page of Project Settings.


#include "LightContainer.h"
#include "Components/PointLightComponent.h"

// Sets default values
ALightContainer::ALightContainer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = SceneRoot;

}

// Called when the game starts or when spawned
void ALightContainer::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALightContainer::ChangeLightColor(FLinearColor newColor)
{
	if (LightComponent) {
		LightComponent->SetLightColor(newColor);
	}
}

FLinearColor ALightContainer::GetLightColor()
{
	if (LightComponent) {
		return LightComponent->GetLightColor();
	}

	return FLinearColor(0, 0, 0, 0);
}

