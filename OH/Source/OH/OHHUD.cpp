// Copyright Epic Games, Inc. All Rights Reserved.

#include "OHHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

AOHHUD::AOHHUD()
{
}

void AOHHUD::DrawHUD()
{
	Super::DrawHUD();
}

void AOHHUD::BeginPlay()
{
	Super::BeginPlay();
	AddUserWidget(HUDWidgetCrosshairClass, HUDWidgetCrosshair);
	AddUserWidget(HUDWidgetGameOverClass, HUDWidgetGameOver);
	AddUserWidget(HUDWidgetInventoryClass, HUDWidgetInventory);
	AddUserWidget(HUDWidgetDialogClass, HUDWidgetDialog);
}

void AOHHUD::AddUserWidget(const TSubclassOf<UUserWidget>& WidgetClass, UUserWidget* Widget)
{
	checkf(WidgetClass, TEXT("Unable to find WidgetClass. Please make sure it is attached in derived blueprint"));

	Widget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

	checkf(Widget, TEXT("Failed to create Widget!"));

	if(Widget == nullptr)
	{
		return;
	}

	Widget->AddToViewport();
}
