// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Buildings/BuildingBase.h"
#include "BuildingGenerator.generated.h"

/**
 * 
 */
UCLASS()
class MICROTYCOON_API ABuildingGenerator : public ABuildingBase
{
	GENERATED_BODY()

public:

	ABuildingGenerator();

	virtual void TickActor(float DeltaTime, ELevelTick TickType, FActorTickFunction& ThisTickFunction) override;

	UFUNCTION(BlueprintPure)
	float GetGeneratedPercent() const;

	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetGenerated() const { return Generated; }
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 GeneratePerMin = 100;

	UPROPERTY(EditDefaultsOnly, Category = Configuration)
	int32 InternalWarehouse = 500;
	
	UPROPERTY(Transient)
	float Generated = .0f;

	virtual void OnBuildFinished() override;
};
