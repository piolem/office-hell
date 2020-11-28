// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OHOpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OH_API UOHOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOHOpenDoor();

	UFUNCTION()
	void OpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DoorOpenTime = 1.f;

	static constexpr float MaxOpenAngleDegrees = 90.f;

	float DoorOpenDirection = 0;
	float DoorOpenProgress = 0.f;
	bool bIsOpened = false;
	FRotator StartDoorRotation;
	FRotator TargetDoorRotation;

	FVector OpenedDoorLocation;
	FVector ClosedDoorLocation;
};
