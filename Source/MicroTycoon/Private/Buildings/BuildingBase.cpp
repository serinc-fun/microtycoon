
#include "Buildings/BuildingBase.h"
#include "Materials/MaterialInterface.h"
#include "Components/MeshComponent.h"

ABuildingBase::ABuildingBase()
{

	PrimaryActorTick.bCanEverTick = true;
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
