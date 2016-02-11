// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Proef_Proeve.h"
#include "Proef_ProeveGameMode.h"
#include "Proef_ProeveCharacter.h"

AProef_ProeveGameMode::AProef_ProeveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
