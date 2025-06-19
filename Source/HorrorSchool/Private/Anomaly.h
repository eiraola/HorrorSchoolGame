// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Anomaly.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnomalyCompleted);

UCLASS()
class AAnomaly : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAnomaly();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere, Category = "Steps")
	TArray<class AStep*> Steps;
	UPROPERTY(EditAnywhere, Category = "Steps")
	class APostProcessController* PostProcessControler;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* GlitchSound;
	int CurrentStepIndex;
	AStep* GetNextStep();
	void ResetAnomaly();
	UFUNCTION()
	void StepCompleted();
	void CompleteAnomaly();
protected:
	AStep* CurrentStep;
public:
	UFUNCTION()
	void StartAnomaly();
	void CancelAnomaly();
	FOnAnomalyCompleted OnAnomalyCompleted;

};
