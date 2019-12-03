// Fill out your copyright notice in the Description page of Project Settings.


#include "MicroTycoonGameModeBase.h"
#include "PlayerCameraPawn.h"
#include "TycoonPlayerController.h"
#include "TycoonPlayerState.h"

AMicroTycoonGameModeBase::AMicroTycoonGameModeBase()
	: Super()
{
	DefaultPawnClass = APlayerCameraPawn::StaticClass();
	PlayerControllerClass = ATycoonPlayerController::StaticClass();
	PlayerStateClass = ATycoonPlayerState::StaticClass();
}
