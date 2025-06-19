// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MenuController.generated.h"

UCLASS()
class AMenuController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMenuController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;
public:
	UPROPERTY(BlueprintReadWrite)
	UUserWidget* MenuWidgetRef;
public:
	UFUNCTION(BlueprintImplementableEvent)
	void ShowMenu();
	UFUNCTION(BlueprintImplementableEvent)
	void HideMenu();
	
};
