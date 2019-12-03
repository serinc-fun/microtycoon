// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCameraPawn.generated.h"

class ABuildingBase;
class UPlayerCursorTraceBuilder;
class UPlayerCursorTraceBase;
class UFloatingPawnMovement;
class USphereComponent;
class UCameraComponent;
class USpringArmComponent;

UENUM(BlueprintType)
enum class EInputSpeedMode : uint8
{
	Base,
	Slow,
	Fast,
	End UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EInputCursorMode : uint8
{
	Selector,
	Builder,
	Destroyer,
	End UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCursorModeChanged, EInputCursorMode, Mode);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingSelected, TSubclassOf<ABuildingBase>, BuildingClass);

UCLASS()
class MICROTYCOON_API APlayerCameraPawn : public APawn
{
	GENERATED_BODY()

public:
	APlayerCameraPawn();
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UPawnMovementComponent* GetMovementComponent() const override;

	UFUNCTION(BlueprintPure, Category = Input)
	float GetMovementSpeed() const;

	UFUNCTION(BlueprintPure, Category = Input)
	float GetZoomSpeed() const;

	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void SetCurrentBuildingTarget(TSubclassOf<ABuildingBase> InBuildingClass);

	UFUNCTION(BlueprintPure, Category = Gameplay)
	FORCEINLINE TSubclassOf<ABuildingBase> GetCurrentBuildingTarget() const { return BuildTarget; }
	
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void SetCursorMode(EInputCursorMode InMode);

	UFUNCTION(BlueprintPure, Category = Gameplay)
	FORCEINLINE EInputCursorMode GetCursorMode() const { return CursorMode; }

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnCursorModeChanged OnCursorModeChanged;

	UPROPERTY(BlueprintAssignable, Category = Events)
	FOnBuildingSelected OnBuildingSelected;
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MovementSpeedBase = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MovementSpeedSlow = 8.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MovementSpeedFast = 50.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	FVector2D ZoomLimits = { 400.0f, 1500.0f };

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float ZoomSpeedBase = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float ZoomSpeedSlow = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float ZoomSpeedFast = 80.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float ZoomSpeedIterp = 12.0f;
	
	UPROPERTY(Transient)
	float TargetZoom;

	UPROPERTY(Transient)
	EInputSpeedMode SpeedMode = EInputSpeedMode::Base;

	UPROPERTY(Transient)
	EInputCursorMode CursorMode = EInputCursorMode::Selector;
	
	UPROPERTY(Transient)
	TSubclassOf<ABuildingBase> BuildTarget;

	UPROPERTY(Transient)
	UPlayerCursorTraceBase* CurrentCursorTrace;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveZoom(float Value);

	template<EInputSpeedMode Value>
	void SwitchSpeedMode()
	{
		SpeedMode = Value;
	}

	void OnMainAction();
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	USphereComponent* SphereComponent;
	
	UPROPERTY(VisibleAnywhere, Category = Components)
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPlayerCursorTraceBuilder* CursorTraceBuilder;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UPlayerCursorTraceBase* CursorTraceBase;
};
