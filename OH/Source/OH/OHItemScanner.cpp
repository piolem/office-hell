// Fill out your copyright notice in the Description page of Project Settings.


#include "OHItemScanner.h"
#include "Camera/CameraComponent.h"

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

    if(!Eye)
    {
        return; // no eye
    }

    // trace line from the component location to the item

    FCollisionQueryParams TraceParams;

    FHitResult Hit;
    FVector StartLocation = Eye->GetComponentLocation();
    FVector EndLocation = StartLocation + Eye->GetComponentRotation().Vector() * 1500.f;

    GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECollisionChannel::ECC_Visibility,
                                         TraceParams, FCollisionResponseParams::DefaultResponseParam);

    bool bItemWasHit = false;
    
    if(Hit.IsValidBlockingHit())
    {
        if(auto* HitActor = Hit.GetActor())
        {
            if(HitActor->ActorHasTag("Interactable"))
            {
                bItemWasHit = true;
                ScannedItem = HitActor;
                SetItemHighlight(true);
            }
        }
    }

    if(!bItemWasHit && ScannedItem)
    {
        SetItemHighlight(false);
        ScannedItem = nullptr;
    }
    // ...
}

void UOHItemScanner::SetItemHighlight(bool Enabled) const
{
    TArray<UStaticMeshComponent*> MeshComponents;
    ScannedItem->GetComponents<UStaticMeshComponent>(MeshComponents);
    for(auto* Component : MeshComponents)
    {
        Component->SetRenderCustomDepth(Enabled);
    }
}
