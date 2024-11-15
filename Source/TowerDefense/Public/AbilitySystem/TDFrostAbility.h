
#pragma once

#include "CoreMinimal.h"
#include "TDTowerAbility.h"
#include "TDFrostAbility.generated.h"

UCLASS()
class TOWERDEFENSE_API UTDFrostAbility : public UTDTowerAbility
{
	GENERATED_BODY()

	virtual void AbilityEffect(AActor* HitActor) override;
};
