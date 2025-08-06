// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.h"
#include "InteractWithObjectStep.generated.h"

class AHorrorSchoolCharacter;
class AInteractable;
UCLASS()
class HORRORSCHOOL_API AInteractWithObjectStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractWithObjectStep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void StartStep() override;
	virtual void EndStep() override;
private:
	AHorrorSchoolCharacter* PlayerCharacter;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AInteractable* InteractableObject;
};
