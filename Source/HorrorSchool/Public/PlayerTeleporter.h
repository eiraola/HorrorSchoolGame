// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerTeleporter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoopFinished);
UCLASS()
class HORRORSCHOOL_API APlayerTeleporter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerTeleporter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* TriggerVolume;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* AppearVolume;
public:
	UFUNCTION()
	void onVolumeBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnLoopFinished OnLoopFinished;
};
