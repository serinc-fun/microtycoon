
#include "Player/PlayerCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
//==================================================
//				For Debug Messages
#include "Engine/Engine.h"

APlayerCameraPawn::APlayerCameraPawn()
{
	SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	SetRootComponent(SphereComponent);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(SphereComponent);
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	MovementComponent->SetUpdatedComponent(SphereComponent);
	
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCameraPawn::MoveRight);
}

UPawnMovementComponent* APlayerCameraPawn::GetMovementComponent() const
{
	return MovementComponent;
}

float APlayerCameraPawn::GetMovementSpeed() const
{
	return MovementSpeedBase;
}

void APlayerCameraPawn::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		const float Speed = GetMovementSpeed() * Value;
		const FVector Direction = GetActorForwardVector();
		AddMovementInput(Direction, Speed);

		GEngine->AddOnScreenDebugMessage(
			static_cast<uint64>(GetUniqueID() + 1),
			3.0f,
			FColorList::LimeGreen,
			FString::Printf(TEXT("MoveForward >> Speed: %.2f, Direction: %s"), Speed, *Direction.ToCompactString())
		);
	}
}

void APlayerCameraPawn::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		const float Speed = GetMovementSpeed() * Value;
		const FVector Direction = GetActorRightVector();
		AddMovementInput(Direction, Speed);

		GEngine->AddOnScreenDebugMessage(
			static_cast<uint64>(GetUniqueID() + 2), 
			3.0f, 
			FColorList::OrangeRed, 
			FString::Printf(TEXT("MoveRight >> Speed: %.2f, Direction: %s"), Speed, *Direction.ToCompactString())
		);
	}
}

void APlayerCameraPawn::MoveZoom(float Value)
{
	
}

void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void APlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
