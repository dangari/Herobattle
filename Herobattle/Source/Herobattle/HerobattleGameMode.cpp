// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Herobattle.h"
#include "HerobattleGameMode.h"
#include "HerobattleCharacter.h"

AHerobattleGameMode::AHerobattleGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
