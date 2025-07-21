// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteractionFinished);

UCLASS(Abstract)
class HORRORSCHOOL_API AInteractable : public AActor
{
	GENERATED_BODY()

public:	
	virtual void Interact() PURE_VIRTUAL(AInteractable::Interact, );
	virtual void Activate() PURE_VIRTUAL(AInteractable::Activate, );
	virtual void Deactivate() PURE_VIRTUAL(AInteractable::Deactivate, );
	FOnInteractionFinished OnInteractionFinished;
		
};
