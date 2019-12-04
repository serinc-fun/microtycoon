
#include "Buildings/BuildingBase.h"
#include "Materials/MaterialInterface.h"
#include "Components/MeshComponent.h"
#include "TimerManager.h"

ABuildingBase::ABuildingBase()
{

	PrimaryActorTick.bCanEverTick = false;
}

void ABuildingBase::SetIndicatorMaterial(UMaterialInterface* InMaterial)
{
	IndicatorMaterial = InMaterial;
	
	TArray<UMeshComponent*> MeshComponents;
	GetComponents<UMeshComponent>(MeshComponents);	

	for (auto MeshComponent : MeshComponents)
	{
		SIZE_T NumMaterials = MeshComponent->GetNumMaterials();
		for (SIZE_T i = 0; i < NumMaterials; ++i)
		{
			MeshComponent->SetMaterial(i, IndicatorMaterial);
		}
	}
}

void ABuildingBase::StartBuild()
{
	if (BuildingState == EBuildingState::Ghost)
	{
		BuildingState = EBuildingState::Build;
		GetWorld()->GetTimerManager().SetTimer(BuildFinishedTimerHandle, this, &ABuildingBase::OnBuildFinished, BuildTime);
	}
}

void ABuildingBase::StartDestroy()
{
	
}

void ABuildingBase::OnBuildFinished()
{
	BuildingState = EBuildingState::Builded;
}
