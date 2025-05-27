// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DoorActor.generated.h"

UCLASS()
class HORRORSCHOOL_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoorActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION(BlueprintImplementableEvent)
	void MoveDoor();
	UFUNCTION(BlueprintCallable)
	void ResetDoor();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* OpenDoorSound;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* DoorStaticMesh;
	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* HolderStaticMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* DoorEndPositionGizmo;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class USceneComponent* DoorBeginPositionGizmo;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* CollisionBox;
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* DoorCollision;
	bool bIsReseted;

};
