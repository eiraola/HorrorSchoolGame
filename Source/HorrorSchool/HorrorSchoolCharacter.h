// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "HorrorSchoolCharacter.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPlayerDead);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableDetected, const FString&, NewText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractableChecking, const bool, isChecking);
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AHorrorSchoolCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/* Sprint Input Action*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* SprintAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float walkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	float runSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* InteractAction;

	
public:
	AHorrorSchoolCharacter();

	void BeginPlay() override;
	void KillPlayer();
	void SetStepSound();
	void SetWetStepSound();
	void StartLookingInteractables();
	void StopLookingInteractables();
protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/* Called for sprint input*/
	void Sprint();

	/* Called for stop sprinting */
	void StopSprint();
	/* Called for sprint input*/
	void Interact();
	UFUNCTION()
	void PlayerDead();

	void PlayerFadeIn();

	void PlayerFadeOut();
	UFUNCTION()
	void CheckInteractables();

protected:
	// APawn interface
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	class USoundBase* StepSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* WetStepSound;
	UPROPERTY( BlueprintReadWrite, Category = "Audio")
	USoundBase* CurrentStepSound;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnPlayerDead OnPlayerDead;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInteractableDetected OnInteractableDetected;
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnInteractableChecking OnInteractableChecking;

protected:
	FTimerHandle DeathTimerHandle;
	FTimerHandle LookForInteractableTimerHandle;
	bool bPlayerIsDead;
	FVector InitialPosition;
	FRotator InitialRotation;
	class AInteractable* CurrentInteractable;

};

