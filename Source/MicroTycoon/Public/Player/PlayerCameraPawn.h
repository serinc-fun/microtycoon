// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCameraPawn.generated.h"

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
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveZoom(float Value);

	template<EInputSpeedMode Value>
	void SwitchSpeedMode()
	{
		SpeedMode = Value;
	}
	
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
};
