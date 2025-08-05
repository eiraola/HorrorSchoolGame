// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Step.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LookAtStep.generated.h"

UCLASS()
class HORRORSCHOOL_API ALookAtStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALookAtStep();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void LookingAt();

public:	
	UFUNCTION()
	void StartStep() override;
	UFUNCTION()
	void EndStep() override;
	void LoadObjects();
	void UnloadObjects();

protected:
	class USceneComponent* RootElement;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StepData")
	class USceneComponent* LookAtPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StepData")
	USceneComponent* StayInPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StepData")
	TArray<AActor*> ActorsToActivate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StepData")
	TArray<AActor*> ActorsToDeactivate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StepData")
	float TimeToPassStep;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StepData")
	float DistanceToLookAt;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StepData")
	float RotationToLookAt;
protected:

	FTimerHandle LookAtTimer;
	float CurrentTimeToPass;
	class AHorrorSchoolCharacter* PlayerActor;
	FTimerHandle TimerHandle;
	
};
