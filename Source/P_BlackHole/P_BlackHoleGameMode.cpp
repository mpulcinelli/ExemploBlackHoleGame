// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "P_BlackHoleGameMode.h"
#include "P_BlackHoleCharacter.h"
#include "UObject/ConstructorHelpers.h"

AP_BlackHoleGameMode::AP_BlackHoleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
