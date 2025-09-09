// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "InteractableTelephone.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class USceneComponent;

UCLASS()
class HORRORSCHOOL_API AInteractableTelephone : public AInteractable
{
	GENERATED_BODY()
	
public:	
	AInteractableTelephone();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Interact() override;
	virtual void Activate() override;
	virtual void Deactivate() override;
	
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* Mesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Collision;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* RingSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* TakePhoneSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	UAudioComponent* AudioComp;
	

};
