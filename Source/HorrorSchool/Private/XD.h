// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XD.generated.h"

UCLASS(Abstract)
class AXD : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AXD();


public:	
	virtual void XDD() PURE_VIRTUAL(AXD::XDD, );
};
