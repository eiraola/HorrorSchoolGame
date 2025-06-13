// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PostProcessController.generated.h"

UCLASS()
class HORRORSCHOOL_API APostProcessController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APostProcessController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PostProcess")
	class APostProcessVolume* PostProcessVolume;
private:
	class UMaterialInstanceDynamic* DynamicMaterialInstance;
public:
	UFUNCTION(BlueprintCallable)
	void ChangeDistorsionValue(float newDistorsion);
	UFUNCTION(BlueprintImplementableEvent)
	void PlayDistorsionEffect();
	
};
