// Fill out your copyright notice in the Description page of Project Settings.


#include "LightActor.h"

#include "Components/PointLightComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/AudioComponent.h"
// Sets default values
ALightActor::ALightActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	LightComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("LightCompoennt"));
	LightComponent->SetupAttachment(RootComponent);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(RootComponent);
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	AudioComponent->SetupAttachment(RootComponent);
	AudioComponent->bAutoActivate = true;
	InitialIntensity = 1.0f;
	InitialVolume = 1.0f;
}

// Called when the game starts or when spawned
void ALightActor::BeginPlay()
{
	Super::BeginPlay();
	InitialColor = LightComponent->GetLightColor();
	InitialIntensity = LightComponent->Intensity;
    AudioComponent->Play();
    InitialVolume = AudioComponent->VolumeMultiplier;
	
	
}

// Called every frame
void ALightActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALightActor::SetLightColor(FLinearColor newColor)
{
	LightComponent->SetLightColor(newColor);
}

FLinearColor ALightActor::GetLightColor()
{
	return LightComponent->GetLightColor();
}

void ALightActor::ResetLightColor()
{
	LightComponent->SetLightColor(InitialColor);
}

void ALightActor::SetLightIntensity(float newIntensity)
{
	newIntensity = FMath::Clamp(newIntensity, 0.0f, 1.0f);
	LightComponent->SetIntensity(InitialIntensity * newIntensity);
}

void ALightActor::SeAudioIntensity(float newIntensity)
{
	AudioComponent->SetVolumeMultiplier(InitialVolume * newIntensity);
}

