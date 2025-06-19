// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Mannequin.generated.h"

UCLASS()
class HORRORSCHOOL_API AMannequin : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMannequin();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void SetNextPosition();
	void SetFirstPosition();
	void SetSecondPosition();
	void SetThirdPosition();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* RootElement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* FirstPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* SecondPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USceneComponent* ThirdPosition;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USkeletalMeshComponent* Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* EnemyCollider;
	UPROPERTY(EditAnywhere, Category = "Spawning", meta = (MakeEditWidget))
	FVector EnemySpawnLocation = FVector(0, 0, 100);
	FVector InitialPos;
	FRotator InitialRotation;

public:
	void Activate();
	void Deactivate();
protected:
	UFUNCTION()
	void OnCapsuleBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
