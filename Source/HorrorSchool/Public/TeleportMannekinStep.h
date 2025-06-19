// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Step.h"
#include "TeleportMannekinStep.generated.h"

UENUM(BlueprintType)
enum class ETeleportNumber : uint8
{
	ET_None     UMETA(DisplayName = "None"),
	ET_First     UMETA(DisplayName = "First"),
	ET_Second     UMETA(DisplayName = "Second"),
	ET_Third     UMETA(DisplayName = "Third")
};

UCLASS()
class HORRORSCHOOL_API ATeleportMannekinStep : public AStep
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleportMannekinStep();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void StartStep() override;
	void EndStep() override;
	void PlayFlickerAnim();
	UFUNCTION()
	void OnManequinColliderBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void TeleportMannequins();

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* RootElement;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* ManequinTeleportCollider;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AMannequin*> Mannequins;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<class AMannequin*> MannequinsToActivate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class ALightsManager* LightsController;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeleportNumber TeleportNumber = ETeleportNumber::ET_First;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
	UAudioComponent* AudioComponent;
protected:
	FTimerHandle TimerHandle;

};
