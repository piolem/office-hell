// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "OHHUD.generated.h"

UCLASS()
class AOHHUD : public AHUD
{
	GENERATED_BODY()

public:
	AOHHUD();

	/** Primary draw call for the HUD */
	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditAnywhere, Category="Widget Templates")
	TSubclassOf<class UUserWidget> HUDWidgetGameOverClass;

	UPROPERTY(EditAnywhere, Category="Widget Templates")
	TSubclassOf<class UUserWidget> HUDWidgetInventoryClass;

	UPROPERTY(EditAnywhere, Category="Widget Templates")
	TSubclassOf<class UUserWidget> HUDWidgetCrosshairClass;

	UPROPERTY(EditAnywhere, Category="Widget Templates")
	TSubclassOf<class UUserWidget> HUDWidgetDialogClass;

	UPROPERTY()
	class UUserWidget* HUDWidgetGameOver;

	UPROPERTY()
	class UUserWidget* HUDWidgetInventory;

	UPROPERTY()
	class UUserWidget* HUDWidgetCrosshair;

	UPROPERTY()
	class UUserWidget* HUDWidgetDialog;

private:
	void AddUserWidget(const TSubclassOf<class UUserWidget>& WidgetClass, class UUserWidget* Widget);	
};

