// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PlayerCameraPawn.generated.h"

class UFloatingPawnMovement;
class USphereComponent;
class UCameraComponent;
class USpringArmComponent;

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
	
protected:

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MovementSpeedBase = 20.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MovementSpeedSlow = 8.0f;

	UPROPERTY(EditDefaultsOnly, Category = Input)
	float MovementSpeedFast = 50.0f;
	
	void MoveForward(float Value);
	void MoveRight(float Value);
	void MoveZoom(float Value);
	
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
