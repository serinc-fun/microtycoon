// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCursorTraceBuilder.h"
#include "Engine/World.h"
#include "Buildings/BuildingBase.h"

UPlayerCursorTraceBuilder::UPlayerCursorTraceBuilder()
	: Super()
{
	
}

void UPlayerCursorTraceBuilder::ToggleTracing(bool Value)
{
	Super::ToggleTracing(Value);

	if (bTracingStarted)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Instigator = Cast<APawn>(GetOwner());
		SpawnParameters.Owner = SpawnParameters.Instigator;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		
		Building = GetWorld()->SpawnActor<ABuildingBase>(BuldingTemplate, SpawnParameters);
		if (Building && Building->IsValidLowLevel())
		{
			Building->SetActorEnableCollision(false);
			Building->SetIndicatorMaterial(Indicator);
		}
	}
	else
	{
		if (Building && Building->IsValidLowLevel())
		{
			Building->Destroy();
			Building = nullptr;
		}
	}
}

void UPlayerCursorTraceBuilder::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bTracingStarted)
	{
		if (Building && Building->IsValidLowLevel())
		{
			Building->SetActorLocation(WorldPoint);
		}
	}
}
