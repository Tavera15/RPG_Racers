// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "RPG_RacersGameMode.h"
#include "RPG_RacersPawn.h"
#include "RPG_RacersHud.h"

ARPG_RacersGameMode::ARPG_RacersGameMode()
{
	DefaultPawnClass = ARPG_RacersPawn::StaticClass();
	HUDClass = ARPG_RacersHud::StaticClass();
}
