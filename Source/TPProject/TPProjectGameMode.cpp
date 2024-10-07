// Copyright Epic Games, Inc. All Rights Reserved.

#include "TPProjectGameMode.h"
#include "TPProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATPProjectGameMode::ATPProjectGameMode()
{
	/*// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Core/Player/Blueprint/BP_BasicCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}*/
}
