// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerCursorTraceBase.generated.h"

/**
 * 
 */
UCLASS()
class MICROTYCOON_API UPlayerCursorTraceBase
	: public UActorComponent
{
	friend class APlayerCameraPawn;
	
	GENERATED_BODY()

public:

	UPlayerCursorTraceBase();
	
	virtual void ToggleTracing(bool Value);

	UFUNCTION(BlueprintPure)
	FORCEINLINE FVector GetWolrdPoint() const { return WorldPoint; }
	
protected:

	UPROPERTY(Transient)
	bool bTracingStarted = false;

	UPROPERTY(Transient)
	FVector WorldPoint;
	
	APlayerController* GetOwnedController() const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool GetWorldCoordinatesForTrace(FVector& OutStart, FVector& OutEnd);
};
