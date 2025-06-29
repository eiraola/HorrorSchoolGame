// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.h"

#include "UnderWaterStep.generated.h"

UCLASS()
class HORRORSCHOOL_API AUnderWaterStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUnderWaterStep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnStartColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnEndColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void KillPlayer();
	UFUNCTION()
	void MoveWater();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void StartStep() override;
	virtual void EndStep() override;

public: 
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* StartCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* EndCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* RootElement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* WaterActor;
	UPROPERTY(EditAnywhere, Category = "WaterPosition", meta = (MakeEditWidget))
	FVector WaterStartLocation = FVector(0, 0, 100);
	UPROPERTY(EditAnywhere, Category = "WaterPosition", meta = (MakeEditWidget))
	FVector WaterEndLocation = FVector(0, 0, 100);
	UPROPERTY(EditAnywhere, Category = "WaterPosition")
	float WaterSpeed;
	
protected:
	class AHorrorSchoolCharacter* PlayerCharacter;
	FTimerHandle WaterMovementTimer;
	FTimerHandle PlayerKillerTimer;
};
