// Fill out your copyright notice in the Description page of Project Settings.


#include "Buildings/BuildingGenerator.h"

ABuildingGenerator::ABuildingGenerator()
	: Super()
{

}

void ABuildingGenerator::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (GetState() == EBuildingState::Builded)
	{
		if (!FMath::IsNearlyEqual(Generated, InternalWarehouse))
		{
			Generated += (float(GeneratePerMin) * DeltaSeconds) / 60.0f;
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

	PrimaryActorTick.bCanEverTick = true;
	SetActorTickEnabled(true);
}
