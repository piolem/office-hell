// Fill out your copyright notice in the Description page of Project Settings.


#include "OHItemScanner.h"

#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UOHItemScanner::UOHItemScanner()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}


// Called when the game starts
void UOHItemScanner::BeginPlay()
{
    Super::BeginPlay();

    // ...
}


// Called every frame
void UOHItemScanner::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // trace line from the component location to the item

    FCollisionQueryParams TraceParams;

    FHitResult Hit;
    FVector StartLocation = GetComponentLocation();
    FVector EndLocation = StartLocation + GetComponentRotation().Vector() * 1500.f;

    GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility,
                                         TraceParams, FCollisionResponseParams::DefaultResponseParam);

   DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Yellow, false, -1, 0, 2.0f);
    // ...
}
