// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "TelephoneInteractable.generated.h"

UCLASS()
class HORRORSCHOOL_API ATelephoneInteractable : public AInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATelephoneInteractable();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	virtual void Interact() override;
	virtual void Activate() override;
	virtual void Deactivate() override;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	class USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Visuals")
	class UMeshComponent* Telephone;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	class UAudioComponent* AudioComponent;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	class USoundBase* RingSound;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio")
	USoundBase* TelephoneSound;
};
