// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_WeaponSystemGameMode.h"
#include "TPS_WeaponSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPS_WeaponSystemGameMode::ATPS_WeaponSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
