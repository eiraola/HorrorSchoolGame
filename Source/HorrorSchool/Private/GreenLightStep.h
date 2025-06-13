// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.h"
#include "GreenLightStep.generated.h"

UCLASS()
class AGreenLightStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGreenLightStep();
public:
	UPROPERTY(EditAnywhere);
	class ALightsManager* LightsManager;
	UPROPERTY(EditAnywhere);
	class UBoxComponent* CompletionCollision;
	UPROPERTY(EditAnywhere);
	class USceneComponent* MonsterPositionGizmo;
	UPROPERTY(EditAnywhere);
	class AMonster* Monster;
	class USceneComponent* SceneRoot;
	float CurrentColor;
	FLinearColor RedColor;
	FLinearColor GreenColor;
	FLinearColor BlueColor;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void SwapLightColor();
	UFUNCTION()
	virtual void StartStep()  override;
	UFUNCTION()
	virtual void EndStep() override ;
	UFUNCTION()
	void OnCompletionCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	FTimerHandle TimerHandle; 
};
