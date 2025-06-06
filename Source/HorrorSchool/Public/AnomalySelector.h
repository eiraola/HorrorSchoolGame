// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AnomalySelector.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnomalyFinished);
UCLASS()
class HORRORSCHOOL_API AAnomalySelector : public AActor
{
	GENERATED_BODY()
	
public:	
	AAnomalySelector();

protected:
	virtual void BeginPlay() override;

public:	
	void StartAnomaly();
	UFUNCTION(BlueprintCallable)
	void SelectAnomaly();
	UFUNCTION()
	void FinishAnomaly();
	UFUNCTION(BlueprintImplementableEvent)
	void OpenLevelDoor();

public: 
	UPROPERTY(EditAnywhere, Category = "Anomalies")
	TArray<class AAnomaly*> Anomalies;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnAnomalyFinished OnAnomalyFinished;
private:
	AAnomaly* CurrentAnomaly;
	int CurrentAnomalyIndex;
};
