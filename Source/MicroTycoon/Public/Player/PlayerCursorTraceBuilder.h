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

	UFUNCTION(BlueprintCallable, Category = Building)
	void SetBuildingClass(TSubclassOf<ABuildingBase> InBuildingClass);

	UFUNCTION(BlueprintPure, Category = Building)
	FORCEINLINE bool IsAllowBuild() const { return bAllowBuild; }
	
protected:

	UPROPERTY(Transient)
	bool bAllowBuild = false;
	
	UPROPERTY(Transient)
	ABuildingBase* Building;

	UPROPERTY(EditDefaultsOnly, Category = Template)
	TSubclassOf<ABuildingBase> BuldingTemplate;

	UPROPERTY(EditDefaultsOnly, Category = Template)
	UMaterialInterface* IndicatorAllow;

	UPROPERTY(EditDefaultsOnly, Category = Template)
	UMaterialInterface* IndicatorDisallow;

	void RefreshBuilding();
};
