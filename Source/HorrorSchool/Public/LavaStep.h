// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Step.h"
#include "LavaStep.generated.h"

/**
 * 
 */
UCLASS()
class HORRORSCHOOL_API ALavaStep : public AStep
{
	GENERATED_BODY()
public:
	ALavaStep();
	virtual void BeginPlay() override;
	virtual void StartStep() override;
	virtual void EndStep() override;
public:
	UPROPERTY(EditDefaultsOnly)
	TArray<AActor*> ActorsToHide;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class UBoxComponent* DamageCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class UBoxComponent* CompletionCollision;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class UBoxComponent* MonsterActivateCollision;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite);
	class AMonster* Monster;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite);
	class USceneComponent* MonsterStartPosition;
protected:
	
	UPROPERTY(BlueprintReadWrite);
	class USceneComponent* RootElement;
	class APawn* PlayerPawn;
	FTimerHandle TimerHandle;
protected:
	UFUNCTION()
	void OnDamageBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnCompletionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnMonsterBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void SetMonsterMoveDirection();
	
};
