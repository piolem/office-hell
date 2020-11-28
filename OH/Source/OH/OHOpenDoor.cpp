// Fill out your copyright notice in the Description page of Project Settings.


#include "OHOpenDoor.h"

// Sets default values for this component's properties
UOHOpenDoor::UOHOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UOHOpenDoor::OpenDoor()
{
	AActor* Owner = GetOwner();

	if(!bIsOpened)
	{
		Owner->SetActorRotation(TargetDoorRotation);
		bIsOpened = true;
	}
	else
	{
		Owner->SetActorRotation(StartDoorRotation);
		bIsOpened = false;
	}
}

// Called when the game starts
void UOHOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	StartDoorRotation = GetOwner()->GetActorRotation();
	TargetDoorRotation = StartDoorRotation + FRotator(0.f, MaxOpenAngleDegrees, 0.f);
	// ...
	
}


// Called every frame
void UOHOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

