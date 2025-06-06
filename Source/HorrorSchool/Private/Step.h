// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStepCompleted);

UCLASS(Abstract)
class AStep : public AActor
{
	GENERATED_BODY()
	

public:	
	virtual void StartStep() PURE_VIRTUAL(AStep::StartStep, );
	virtual void EndStep() PURE_VIRTUAL(AStep::EndStep, );
	FOnStepCompleted OnStepCompleted;
};
