#pragma once

#include "CoreMinimal.h"
#include "Towers/TDTowerProjectile.h"
#include "TDTowerTrackerProjectile.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDTowerTrackerProjectile : public ATDTowerProjectile
{
	GENERATED_BODY()

public:
	ATDTowerTrackerProjectile();

	virtual void Initialize(float InSpeed, AActor* InTargetActor) override;
	
	AActor* TargetActor;
	
public:
	virtual void Tick(float DeltaTime) override;
};
