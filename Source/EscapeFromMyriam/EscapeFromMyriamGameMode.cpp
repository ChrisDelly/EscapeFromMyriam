// Copyright Epic Games, Inc. All Rights Reserved.

#include "EscapeFromMyriamGameMode.h"
#include "EscapeFromMyriamCharacter.h"
#include "UObject/ConstructorHelpers.h"

AEscapeFromMyriamGameMode::AEscapeFromMyriamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
