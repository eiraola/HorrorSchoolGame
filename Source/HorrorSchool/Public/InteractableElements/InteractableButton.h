// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "InteractableButton.generated.h"

class UStaticMeshComponent;
class UMaterialInstanceDynamic;
class USceneComponent;
class UBoxComponent;
/**
 * 
 */
UCLASS()
class HORRORSCHOOL_API AInteractableButton : public AInteractable
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	const FName MaterialEmissionName = "Emission";
public:
	AInteractableButton();
	virtual void Interact() override;
	virtual void Activate() override;
	virtual void Deactivate() override;
	void RestartButton();
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* ButtonMesh;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USceneComponent* Root;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* Collision;
	UPROPERTY()
	UMaterialInstanceDynamic* DynamicMaterial;
private:
	bool IsUsed;
	void Use();
	


};
