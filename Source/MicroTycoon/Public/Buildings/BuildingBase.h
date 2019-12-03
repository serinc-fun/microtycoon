// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

UCLASS()
class MICROTYCOON_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildingBase();

	void SetIndicatorMaterial(UMaterialInterface* InMaterial);
	
protected:

	UPROPERTY(Transient)
	UMaterialInterface* IndicatorMaterial;
};
