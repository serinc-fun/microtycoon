// Fill out your copyright notice in the Description page of Project Settings.


#include "MicroTycoonGameModeBase.h"
#include "PlayerCameraPawn.h"

AMicroTycoonGameModeBase::AMicroTycoonGameModeBase()
	: Super()
{
	DefaultPawnClass = APlayerCameraPawn::StaticClass();
}
