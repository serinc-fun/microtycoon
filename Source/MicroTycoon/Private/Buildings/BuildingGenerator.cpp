// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingGenerator.h"

ABuildingGenerator::ABuildingGenerator()
	: Super()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABuildingGenerator::TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction)
{
	Super::TickActor(DeltaTime, TickType, ThisTickFunction);

	if (GetState() == EBuildingState::Builded)
	{
		if (Generated < InternalWarehouse)
		{
			Generated = FMath::Clamp<float>(Generated + (float(GeneratePerMin) * DeltaTime) / 60.0f, .0f, InternalWarehouse);
		}
	}
}

float ABuildingGenerator::GetGeneratedPercent() const
{
	if (!FMath::IsNearlyZero(Generated) && InternalWarehouse > 0)
	{
		return Generated / float(InternalWarehouse);
	}

	return .0f;
}

void ABuildingGenerator::OnBuildFinished()
{
	Super::OnBuildFinished();
}
