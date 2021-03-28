// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPS_WeaponSystemGameMode.h"
#include "TPS_WeaponSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPS_WeaponSystemGameMode::ATPS_WeaponSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_PlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(
		TEXT("/Game/Blueprints/BP_TPSPlayerController"));
	if (PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}
