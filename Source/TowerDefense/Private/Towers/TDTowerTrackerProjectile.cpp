#include "Towers/TDTowerTrackerProjectile.h"


ATDTowerTrackerProjectile::ATDTowerTrackerProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATDTowerTrackerProjectile::Initialize(float InSpeed, AActor* InTargetActor)
{
	Super::Initialize(InSpeed, TargetActor);
	TargetActor = InTargetActor;
}

void ATDTowerTrackerProjectile::Tick(float DeltaTime)
{
	if(IsValid(TargetActor))
	{
		FVector Direction = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal();
		Direction.Z = 0;
		FRotator NewRotation = Direction.Rotation();
		SetActorRotation(NewRotation);
	}
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime, true);
}

