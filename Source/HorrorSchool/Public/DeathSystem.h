// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DeathSystem.generated.h"

UCLASS()
class HORRORSCHOOL_API ADeathSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADeathSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	void OnPlayerDead();
protected:
	class AHorrorSchoolCharacter* PlayerCharacter;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AAnomalySelector* AnomalySelector;

};
