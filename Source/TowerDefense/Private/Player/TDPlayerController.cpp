#include "Player/TDPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/TDClickable.h"
#include "Interfaces/TDHoverable.h"
#include "Player/TDPlayerPawn.h"

class UEnhancedInputLocalPlayerSubsystem;

ATDPlayerController::ATDPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDPlayerController::OnLeftClickOnTowerSlot()
{
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FHitResult HitResult;
	FVector WorldLocation, WorldDirection;
	DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);

	FVector TraceEnd = WorldLocation + (WorldDirection * 1000000);
	GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, TraceEnd, ECC_Visibility);
	ITDClickable* ClickableActor = Cast<ITDClickable>(HitResult.GetActor());
	if (HitResult.bBlockingHit && ClickableActor != nullptr)
	{
		ClickableActor->OnClick();
	}
}

void ATDPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		Subsystem->AddMappingContext(IMC_Default, 0);
	}
	bShowMouseCursor = true;
}

void ATDPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	FVector2D MousePosition;
	GetMousePosition(MousePosition.X, MousePosition.Y);
	
	FHitResult HitResult;
	FVector WorldLocation, WorldDirection;
	DeprojectScreenPositionToWorld(MousePosition.X, MousePosition.Y, WorldLocation, WorldDirection);

	FVector TraceEnd = WorldLocation + (WorldDirection * 1000000);
	GetWorld()->LineTraceSingleByChannel(HitResult, WorldLocation, TraceEnd, ECC_Visibility);
	ITDHoverable* HoverableActor = Cast<ITDHoverable>(HitResult.GetActor());

	if (HitResult.bBlockingHit && HoverableActor != nullptr)
	{
		if(CurrentHoveredElement.GetObject() != HitResult.GetActor())
		{
			if(CurrentHoveredElement.GetObject() != nullptr)
			{
				CurrentHoveredElement->OnStopHover();
			}

			CurrentHoveredElement.SetInterface(HoverableActor);
			CurrentHoveredElement.SetObject(HitResult.GetActor());	
			CurrentHoveredElement->OnStartHover();
		}
	}
	else
	{
		if(CurrentHoveredElement != nullptr)
		{
			CurrentHoveredElement->OnStopHover();
			CurrentHoveredElement = nullptr;
		}
	}
}

void ATDPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	Super::SetupInputComponent();
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(IA_LeftClickOnTower, ETriggerEvent::Triggered, this, &ATDPlayerController::OnLeftClickOnTowerSlot);
	}
}


