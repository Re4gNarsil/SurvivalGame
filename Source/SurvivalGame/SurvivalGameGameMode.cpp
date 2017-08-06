// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "SurvivalGame.h"
#include "SurvivalGameGameMode.h"
#include "SurvivalGameHUD.h"
#include "SurvivalGameCharacter.h"

ASurvivalGameGameMode::ASurvivalGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Dynamic/FirstPerson/Blueprints/SGCFirstPersonCharacter_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ASurvivalGameHUD::StaticClass();
}
