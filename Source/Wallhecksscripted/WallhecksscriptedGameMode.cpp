// Copyright Epic Games, Inc. All Rights Reserved.

#include "WallhecksscriptedGameMode.h"
#include "WallhecksscriptedCharacter.h"
#include "UObject/ConstructorHelpers.h"

AWallhecksscriptedGameMode::AWallhecksscriptedGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
