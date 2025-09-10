// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Step.h"
#include "PushButtonsStep.generated.h"

/**
 * 
 */

class AInteractableButton;
class AHorrorSchoolCharacter;
UCLASS()
class HORRORSCHOOL_API APushButtonsStep : public AStep
{
	GENERATED_BODY()
public:
	APushButtonsStep();
	virtual void BeginPlay();
public:
	virtual void StartStep() override;
	virtual void EndStep() override;
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buttons");
	TObjectPtr<AInteractableButton> RedButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buttons");
	TObjectPtr<AInteractableButton> YellowButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buttons");
	TObjectPtr<AInteractableButton> BlueButton;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Buttons");
	TObjectPtr<AInteractableButton> GreenButton;

private:
	UFUNCTION()
	void OnRedButtonPressed();
	UFUNCTION()
	void OnYellowButtonPressed();
	UFUNCTION()
	void OnBlueButtonPressed();
	UFUNCTION()
	void OnGreenButtonPressed();
	UFUNCTION()
	void ResetButons();
private:
	int CurrentIndex;
	AHorrorSchoolCharacter* PlayerCharacter;
	
};
