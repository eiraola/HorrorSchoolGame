// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Step.h"
#include "GameFramework/Actor.h"
#include "EnemyStep.generated.h"

UCLASS()
class HORRORSCHOOL_API AEnemyStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyStep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnyWhere);
	class UBoxComponent* EncounterCollision;
	UPROPERTY(EditAnyWhere);
	UBoxComponent* RunCollision;
	UPROPERTY(EditAnyWhere);
	class USceneComponent* StartingPoint;
	UPROPERTY(EditAnyWhere);
	USceneComponent* EndingPoint;
	UPROPERTY(EditAnyWhere);
	USceneComponent* RootPoint;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "Pawn")
	class AMonster* EnemyMonster;

	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
	virtual void StartStep() override;
	UFUNCTION()
	virtual void EndStep() override;

protected:

	UFUNCTION()
	void OnEncounterCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnRunCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};


