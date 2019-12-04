// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

UENUM(BlueprintType)
enum class EBuildingState : uint8
{
	Ghost,
	Build,
	Builded,
	Destroy,
	End UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingStateChanged, EBuildingState, State);

UCLASS()
class MICROTYCOON_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:	
	ABuildingBase();

	void SetIndicatorMaterial(UMaterialInterface* InMaterial);

	UFUNCTION(BlueprintPure, Category = Resource)
	FORCEINLINE int32 GetBuildCost() const { return TycoonsBuildCost; }

	UFUNCTION(BlueprintPure, Category = Resource)
	FORCEINLINE float GetBuildTime() const { return BuildTime; }

	UFUNCTION(BlueprintPure, Category = Gameplay)
	FORCEINLINE EBuildingState GetState() const { return BuildingState; }
	
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void StartBuild();

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void StartDestroy();

	UPROPERTY(BlueprintAssignable)
	FOnBuildingStateChanged OnBuildingStateChanged;
	
protected:

	UPROPERTY(Transient)
	UMaterialInterface* IndicatorMaterial;

	UPROPERTY(Transient)
	EBuildingState BuildingState = EBuildingState::Ghost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Description)
	FText BuildingName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Description)
	FText BuildingDescription;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Resource)
	int32 TycoonsBuildCost;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Configuration)
	float BuildTime = 3.0f;

	UFUNCTION()
	virtual void OnBuildFinished();

	UFUNCTION()
	void SetStateInternal(EBuildingState InState);

	FTimerHandle BuildFinishedTimerHandle;
};
