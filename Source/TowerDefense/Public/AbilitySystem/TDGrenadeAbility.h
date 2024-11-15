#pragma once

#include "CoreMinimal.h"
#include "TDTowerAbility.h"
#include "TDGrenadeAbility.generated.h"

UCLASS()
class TOWERDEFENSE_API UTDGrenadeAbility : public UTDTowerAbility
{
	GENERATED_BODY()

	virtual void AbilityEffect(AActor* HitActor) override;
};
