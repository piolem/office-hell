// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Character.h"
#include "OHCharacter.generated.h"
class UInputComponent;
 
UCLASS(config=Game)
class AOHCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

public:
	AOHCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* PickupSound;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Gameplay)
	class UOHItemScanner* ItemScanner;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Gameplay)
	class UOHInventoryComponent* Inventory;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category=Gameplay)
	class UOHDialogComponent* DialogComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Audio)
	class UAudioComponent* AudioComponent;

	UFUNCTION(BlueprintCallable)
	void EndConversation();

	UFUNCTION(BlueprintImplementableEvent)
	void EventOnDoorOpened(AActor* DoorActor);

	UFUNCTION(BlueprintImplementableEvent)
	void EventOnConversationEnded(AActor* OtherActor);

protected:
	void OnOpenDoor(AActor* ScannedActor);
	void OnStartConversation(AActor* Actor);
	void OnInteract();
	
	/** Called every time we pick up something */
	void OnPickup(AActor* ItemActor, bool bShouldDestroy);

	void OnToggleInventory();
	
	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	bool bIsShowingInventory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	bool bIsShowingGameOver;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="UI")
	bool bIsConversationActive;

	UPROPERTY()
	AActor* Conversee;
	
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

