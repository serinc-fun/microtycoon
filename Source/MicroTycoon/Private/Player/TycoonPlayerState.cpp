// Fill out your copyright notice in the Description page of Project Settings.


#include "TycoonPlayerState.h"

ATycoonPlayerState::ATycoonPlayerState()
	: Super()
{
	
}

bool ATycoonPlayerState::GiveResource(const int32& InResource)
{
	int32 Result = Tycoons + InResource;	
	if (Result < 0) return false;
	Tycoons = Result;
	return true;
}
