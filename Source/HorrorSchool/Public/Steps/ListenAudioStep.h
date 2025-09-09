// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.h"
#include "ListenAudioStep.generated.h"

class USoundBase;
class UAudioComponent;
UCLASS()
class HORRORSCHOOL_API AListenAudioStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AListenAudioStep();
	UFUNCTION()
	virtual void StartStep() override;
	UFUNCTION()
	virtual void EndStep() override;
	UFUNCTION()
	void OnAudioFinished();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	float CurrentAudio;

public:	

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* SoundSource;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TArray<USoundBase*> Audios;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* AudioComp;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float TimeBetweenAudios;

};
