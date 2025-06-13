// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LightActor.generated.h"

UCLASS()
class HORRORSCHOOL_API ALightActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALightActor();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UPointLightComponent> LightComponent;
	UPROPERTY(BlueprintReadWrite)
	class USceneComponent* SceneRoot;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetLightColor(FLinearColor newColor);
	FLinearColor GetLightColor();
	void ResetLightColor();
private:

	FLinearColor InitialColor;
};
