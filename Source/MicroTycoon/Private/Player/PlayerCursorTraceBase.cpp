// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCursorTraceBase.h"
#include "PlayerCameraPawn.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

UPlayerCursorTraceBase::UPlayerCursorTraceBase()
	: Super()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerCursorTraceBase::ToggleTracing(bool Value)
{
	bTracingStarted = Value;
}

APlayerController* UPlayerCursorTraceBase::GetOwnedController() const
{
	APawn* PawnOwner = Cast<APawn>(GetOwner());	
	if (IsValid(PawnOwner))
	{
		return PawnOwner->GetController<APlayerController>();
	}

	return nullptr;
}

void UPlayerCursorTraceBase::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (bTracingStarted)
	{
		FVector TraceStart;
		FVector TraceEnd;
		
		if (GetWorldCoordinatesForTrace(TraceStart, TraceEnd))
		{
			WorldPoint = TraceStart;
			
			FHitResult HitResult;
			FCollisionQueryParams QueryParams(TEXT("FindWorldLocationFromCuror"), false, GetOwner());
			
			if (GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_WorldStatic, QueryParams))
			{
				WorldPoint = HitResult.Location;

				::DrawDebugPoint(GetWorld(), TraceStart, 10, FColorList::LimeGreen);
				::DrawDebugPoint(GetWorld(), WorldPoint, 10, FColorList::OrangeRed);
			}
		}
	}
}

bool UPlayerCursorTraceBase::GetWorldCoordinatesForTrace(FVector& OutStart, FVector& OutEnd)
{
	auto MyController = GetOwnedController();
	if (MyController && MyController->IsValidLowLevel())
	{		
		MyController->DeprojectMousePositionToWorld(OutStart, OutEnd);
		
		OutEnd = OutStart + OutEnd * 5000.0f;
		return true;
	}

	return false;
}

