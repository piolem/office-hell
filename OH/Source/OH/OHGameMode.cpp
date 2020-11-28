// Copyright Epic Games, Inc. All Rights Reserved.

#include "OHGameMode.h"
#include "OHHUD.h"
#include "OHCharacter.h"
#include "UObject/ConstructorHelpers.h"

AOHGameMode::AOHGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}
