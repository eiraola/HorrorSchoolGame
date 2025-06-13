// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightContainer.generated.h"

UCLASS()
class HORRORSCHOOL_API ALightContainer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightContainer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPointLightComponent> LightComponent;
	UPROPERTY(BlueprintReadWrite)
	class USceneComponent* SceneRoot;


public:	
	void ChangeLightColor(FLinearColor newColor);
	FLinearColor GetLightColor();

};
