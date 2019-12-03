// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/PlayerCursorTraceBase.h"
#include "PlayerCursorTraceBuilder.generated.h"

class UMaterialInterface;
class ABuildingBase;
/**
 * 
 */
UCLASS()
class MICROTYCOON_API UPlayerCursorTraceBuilder : public UPlayerCursorTraceBase
{
	GENERATED_BODY()

public:

	UPlayerCursorTraceBuilder();

	virtual void ToggleTracing(bool Value) override;
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	UPROPERTY(Transient)
	ABuildingBase* Building;

	UPROPERTY(EditDefaultsOnly, Category = Template)
	TSubclassOf<ABuildingBase> BuldingTemplate;

	UPROPERTY(EditDefaultsOnly, Category = Template)
	UMaterialInterface* Indicator;
};
