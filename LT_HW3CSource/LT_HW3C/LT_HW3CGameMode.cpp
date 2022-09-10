// Copyright Epic Games, Inc. All Rights Reserved.

#include "LT_HW3CGameMode.h"
#include "LT_HW3CCharacter.h"
#include "UObject/ConstructorHelpers.h"

ALT_HW3CGameMode::ALT_HW3CGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
