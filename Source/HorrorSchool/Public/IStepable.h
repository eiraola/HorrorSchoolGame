// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IStepable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIStepable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class HORRORSCHOOL_API IIStepable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual bool StartStep() = 0;
	virtual void EndStep() = 0;
};
