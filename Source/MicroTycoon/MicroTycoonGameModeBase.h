// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MicroTycoonGameModeBase.generated.h"

class ABuildingBase;
/**
 * 
 */
UCLASS()
class MICROTYCOON_API AMicroTycoonGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AMicroTycoonGameModeBase();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Buildings)
	TArray<TSubclassOf<ABuildingBase>> AllowedBuildings;
};
