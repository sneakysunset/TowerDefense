#pragma once

#include "CoreMinimal.h"
#include "TDTowerAbility.h"
#include "TDSubmachineGunAbility.generated.h"


UCLASS()
class TOWERDEFENSE_API UTDSubmachineGunAbility : public UTDTowerAbility
{
	GENERATED_BODY()

protected:
	virtual void AbilityEffect(AActor* HitActor) override;

};
