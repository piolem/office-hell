// Fill out your copyright notice in the Description page of Project Settings.


#include "OHInventoryComponent.h"
#include "InventoryBack.h"

namespace OHInventoryComponentCVars
{
	// Listen server smoothing
	static int32 DebugListInventoryItems = 1;
	FAutoConsoleVariableRef CVarNetEnableListenServerSmoothing(
        TEXT( "oh.DebugListInventory" ),
        DebugListInventoryItems,
        TEXT( "Show debug inventory items.\n" ) TEXT( "0: Disable, 1: Enable" ),
        ECVF_Default );
}

// Sets default values for this component's properties
UOHInventoryComponent::UOHInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOHInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOHInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(OHInventoryComponentCVars::DebugListInventoryItems > 0)
	{
		DebugDisplayItems();
		OHInventoryComponentCVars::DebugListInventoryItems = 0;
	}
	// ...
}

void UOHInventoryComponent::AddItem(FString UniqueItemName)
{
	Backend.add_item(std::string(TCHAR_TO_UTF8(*UniqueItemName)));
}

void UOHInventoryComponent::RemoveItem(FString UniqueItemName)
{
	Backend.remove_item(std::string(TCHAR_TO_UTF8(*UniqueItemName)));
}

void UOHInventoryComponent::RemoveAllItems()
{
	for(int i = 0; i < InventoryBack::MaxInventorySlots; ++i)
	{
		Backend.Slot[i] = InventoryBack::EmptyInventorySlot;
	}
}

void UOHInventoryComponent::DebugDisplayItems()
{
	for(int i = 0; i < InventoryBack::MaxInventorySlots; ++i)
	{
		if(Backend.Slot[i] != InventoryBack::EmptyInventorySlot)
		{
			UE_LOG(LogTemp, Warning, TEXT("Inventory item: %i :: %s"), i, UTF8_TO_TCHAR(Backend.Slot[i].c_str()));
		}
	}
}

