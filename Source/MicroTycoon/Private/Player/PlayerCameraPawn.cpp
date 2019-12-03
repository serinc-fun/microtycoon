
#include "Player/PlayerCameraPawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCursorTraceBase.h"
#include "PlayerCursorTraceBuilder.h"
//==================================================
//				For Debug Messages
#include "Engine/Engine.h"
//==================================================
#include "TycoonPlayerState.h"
#include "Buildings/BuildingBase.h"

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

	TargetZoom = FMath::Lerp(ZoomLimits.X, ZoomLimits.Y, 0.3f);
	
	PrimaryActorTick.bCanEverTick = true;
	
	CursorTraceBuilder = CreateDefaultSubobject<UPlayerCursorTraceBuilder>(TEXT("PlayerCursorTraceBuilder"));
	CursorTraceBase = CreateDefaultSubobject<UPlayerCursorTraceBase>(TEXT("PlayerCursorTraceBase"));
}

void APlayerCameraPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCameraPawn::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCameraPawn::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("MoveZoom"), this, &APlayerCameraPawn::MoveZoom);

	PlayerInputComponent->BindAction(TEXT("SpeedSlow"), IE_Pressed, this, &APlayerCameraPawn::SwitchSpeedMode<EInputSpeedMode::Slow>);
	PlayerInputComponent->BindAction(TEXT("SpeedSlow"), IE_Released, this, &APlayerCameraPawn::SwitchSpeedMode<EInputSpeedMode::Base>);
	
	PlayerInputComponent->BindAction(TEXT("SpeedFast"), IE_Pressed, this, &APlayerCameraPawn::SwitchSpeedMode<EInputSpeedMode::Fast>);
	PlayerInputComponent->BindAction(TEXT("SpeedFast"), IE_Released, this, &APlayerCameraPawn::SwitchSpeedMode<EInputSpeedMode::Base>);

	PlayerInputComponent->BindAction(TEXT("MainAction"), IE_Pressed, this, &APlayerCameraPawn::OnMainAction);
}

UPawnMovementComponent* APlayerCameraPawn::GetMovementComponent() const
{
	return MovementComponent;
}

float APlayerCameraPawn::GetMovementSpeed() const
{
	switch(SpeedMode) 
	{		
		case EInputSpeedMode::Slow: return MovementSpeedSlow;
		case EInputSpeedMode::Fast: return MovementSpeedFast;
		default: return MovementSpeedBase;
	}
}

float APlayerCameraPawn::GetZoomSpeed() const
{
	switch (SpeedMode)
	{
		case EInputSpeedMode::Slow: return ZoomSpeedSlow;
		case EInputSpeedMode::Fast: return ZoomSpeedFast;
		default: return ZoomSpeedBase;
	}
}

void APlayerCameraPawn::SetCurrentBuildingTarget(TSubclassOf<ABuildingBase> InBuildingClass)
{
	BuildTarget = InBuildingClass;

	if (CursorMode == EInputCursorMode::Builder)
	{
		CursorTraceBuilder->SetBuildingClass(BuildTarget);
	}

	OnBuildingSelected.Broadcast(BuildTarget);
}

void APlayerCameraPawn::SetCursorMode(EInputCursorMode InMode)
{
	CursorMode = InMode;

	if (CurrentCursorTrace && CurrentCursorTrace->IsValidLowLevel())
	{
		CurrentCursorTrace->ToggleTracing(false);
	}
	
	switch (CursorMode) 
	{
		case EInputCursorMode::Builder:
			CurrentCursorTrace = CursorTraceBuilder;
		break;
		default:
			CurrentCursorTrace = CursorTraceBase;
	}

	if (CurrentCursorTrace && CurrentCursorTrace->IsValidLowLevel())
	{
		CurrentCursorTrace->ToggleTracing(true);
	}

	OnCursorModeChanged.Broadcast(CursorMode);
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
	if (!FMath::IsNearlyZero(Value))
	{
		TargetZoom = FMath::Clamp(TargetZoom - GetZoomSpeed() * Value, ZoomLimits.X, ZoomLimits.Y);

		GEngine->AddOnScreenDebugMessage(
			static_cast<uint64>(GetUniqueID() + 3),
			3.0f,
			FColorList::OrangeRed,
			FString::Printf(TEXT("MoveZoom >> TargetZoom: %.2f"), TargetZoom)
		);
	}
}

void APlayerCameraPawn::OnMainAction()
{
	// TODO: Place building, destroy and select code here.
	switch (CursorMode) 
	{
		case EInputCursorMode::Builder:
		{
			if (BuildTarget)
			{
				if (CursorTraceBuilder && CursorTraceBuilder->IsValidLowLevel())
				{
					if (auto MyPlayerState = GetPlayerState<ATycoonPlayerState>())
					{
						if (MyPlayerState->GiveResource(-BuildTarget.GetDefaultObject()->GetBuildCost()))
						{
							FTransform SpawnTransform(CursorTraceBuilder->GetWolrdPoint());
							
							FActorSpawnParameters SpawnParameters;
							SpawnParameters.Instigator = this;
							SpawnParameters.Owner = SpawnParameters.Instigator;
							SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

							GetWorld()->SpawnActor<ABuildingBase>(BuildTarget, SpawnTransform, SpawnParameters);
						}
					}
				}
				break;
			}
		}
		default: ;
	}
}

void APlayerCameraPawn::BeginPlay()
{
	Super::BeginPlay();

	if (auto MyController = Cast<APlayerController>(GetController()))
	{
		MyController->SetInputMode(FInputModeGameAndUI().SetHideCursorDuringCapture(false));
		MyController->bShowMouseCursor = true;
	}
}

void APlayerCameraPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SpringArmComponent->TargetArmLength = FMath::FInterpTo(SpringArmComponent->TargetArmLength, TargetZoom, DeltaTime, ZoomSpeedIterp);
}
