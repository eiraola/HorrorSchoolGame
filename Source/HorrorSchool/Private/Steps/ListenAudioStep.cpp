// Fill out your copyright notice in the Description page of Project Settings.


#include "Steps/ListenAudioStep.h"
#include "Sound/SoundBase.h"
#include "Components/AudioComponent.h"

// Sets default values
AListenAudioStep::AListenAudioStep()
{
	PrimaryActorTick.bCanEverTick = false;
	CurrentAudio = 0;
	Root = CreateDefaultSubobject<USceneComponent>("RootComponent");
	RootComponent = Root;
	SoundSource = CreateDefaultSubobject<USceneComponent>("SoundSource");
	SoundSource->SetupAttachment(RootComponent);
	AudioComp = CreateDefaultSubobject<UAudioComponent>("AudioComponent");
	AudioComp->SetupAttachment(RootComponent);
}

void AListenAudioStep::StartStep()
{
	CurrentAudio = 0;
	if (Audios.Num() > 0) {
		AudioComp->Sound = Audios[CurrentAudio];
		AudioComp->OnAudioFinished.AddDynamic(this, &AListenAudioStep::OnAudioFinished);
		AudioComp->Play();
	}
}

void AListenAudioStep::EndStep()
{
	CurrentAudio = 0;
	AudioComp->OnAudioFinished.RemoveDynamic(this, &AListenAudioStep::OnAudioFinished);
	OnStepCompleted.Broadcast();
}

void AListenAudioStep::OnAudioFinished()
{
	CurrentAudio++;
	if (Audios.IsValidIndex(CurrentAudio)) {
		AudioComp->Sound = Audios[CurrentAudio];
		AudioComp->Play();
		return;
	}

	EndStep();
}

void AListenAudioStep::BeginPlay()
{
	Super::BeginPlay();
	AudioComp->SetRelativeLocation(SoundSource->GetComponentLocation());
	
}


