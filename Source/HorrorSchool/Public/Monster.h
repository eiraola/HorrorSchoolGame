// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Monster.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPositionReached);

UCLASS()
class HORRORSCHOOL_API AMonster : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMonster();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
private:
	FVector TargetPosition;
	float TargetSpeed;
	bool bIsMoving;
public:
	void SetTargetVector(FVector targetPosition);
	void StartMovement();
	void StopMovement();
	void SetTargetSpeed(float targetSpeed);
	void Activate();
	void Deactivate();
	FOnPositionReached OnPositionReached;
};
