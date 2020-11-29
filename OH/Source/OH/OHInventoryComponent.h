// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "InventoryBack.h"

#include "OHInventoryComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OH_API UOHInventoryComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOHInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(FString UniqueItemName);

	UFUNCTION(BlueprintCallable)		
	void RemoveItem(FString UniqueItemName);

	UFUNCTION(BlueprintCallable)
	bool HasItem(FString UniqueItemName);

	void RemoveAllItems();

	void DebugDisplayItems();

	// obtain copy of the items collection to be displayed
	UFUNCTION(BlueprintCallable)
	TArray<FString> GetCopy() const;

	// synchronize items with the copy
	UFUNCTION(BlueprintCallable)
	void Sync(const TArray<FString> Copy);

private:
	InventoryBack Backend;
};
