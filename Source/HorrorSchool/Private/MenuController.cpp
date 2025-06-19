// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
AMenuController::AMenuController()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AMenuController::BeginPlay()
{
	Super::BeginPlay();
    if (MenuWidgetClass)
    {
        APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
        MenuWidgetRef = CreateWidget<UUserWidget>(PC, MenuWidgetClass);
        if (MenuWidgetRef)
        {
            MenuWidgetRef->AddToViewport();
            MenuWidgetRef->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}


