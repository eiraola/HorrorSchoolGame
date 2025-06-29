// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.h"
#include "PlayerFollowerMonsterStep.generated.h"

UCLASS()
class HORRORSCHOOL_API APlayerFollowerMonsterStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerFollowerMonsterStep();

protected:
	
	virtual void BeginPlay() override;
public:
	virtual void StartStep() override;
	virtual void EndStep() override;
protected:
	class APawn* PlayerCharacter;
	FTimerHandle TimerHandle;
	UFUNCTION()
	void ChasePlayer();
	UFUNCTION()
	void OnColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AMonster* Monster;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bDeactivateMonsterOnEnd;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MonsterSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* EndCollision;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Root;
};
