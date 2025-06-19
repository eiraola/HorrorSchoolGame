// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightsManager.generated.h"

UCLASS()
class ALightsManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightsManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	FLinearColor InitialColor;
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Lights")
	TArray<class ALightActor*> PointLightComponents;

public:
	UFUNCTION()
	void ChangeLightsColor(FLinearColor newColor);
	void ResetLights();
	void DoFlickerAnimation();
};
