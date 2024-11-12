#include "Player/TDPlayerPawn.h"

#include "Blueprint/UserWidget.h"

ATDPlayerPawn::ATDPlayerPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATDPlayerPawn::BeginPlay()
{
	Super::BeginPlay();
}

void ATDPlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

