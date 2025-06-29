// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Step.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MoveMonsterToPosition.generated.h"

UCLASS()
class HORRORSCHOOL_API AMoveMonsterToPositionStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMoveMonsterToPositionStep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	virtual void StartStep() override;
	UFUNCTION()
	virtual void EndStep() override;
protected:
	class USceneComponent* Root;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float EnemySpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShouldHideEnemyOnFinish;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMonster* Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* StartPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* EndPosition;


};
