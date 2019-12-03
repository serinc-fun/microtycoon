// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TycoonPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class MICROTYCOON_API ATycoonPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	ATycoonPlayerState();

	UFUNCTION(BlueprintPure, Category = Resource)
	FORCEINLINE int32 GetCurrentResource() const { return Tycoons; }

	UFUNCTION(BlueprintCallable, Category = Resource)
	bool GiveResource(const int32& InResource);
	
protected:
	
	UPROPERTY(EditDefaultsOnly, Category = Resource)
	int32 Tycoons = 500;
	
};
