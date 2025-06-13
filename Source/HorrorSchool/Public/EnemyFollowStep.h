// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.h"
#include "EnemyFollowStep.generated.h"

UCLASS()
class HORRORSCHOOL_API AEnemyFollowStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyFollowStep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void StartStep() override;
	void EndStep() override;
	void SetMonsterDirection();
	UFUNCTION() 
	void OnEnemyEncounterCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndStepCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEnemyStairsReach();

public:	
	UPROPERTY(EditAnywhere)
	class UBoxComponent* EnemyEncounterCollision;
	UPROPERTY(EditAnywhere)
	UBoxComponent* StepEndCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	class AMonster* Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	class AActor* ObstacleObject;
	UPROPERTY(EditAnywhere)
	class USceneComponent* EnemyStartPosition;
	UPROPERTY(EditAnywhere)
	USceneComponent* EnemyReachPosition;
	USceneComponent* RootElement;
protected:
	FTimerHandle TimerHandle;
	class APawn* PlayerPawn;
	bool bIsEnemyAwake;

};
