// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/TDTowerAbility.h"
#include "TDTeslaAbility.generated.h"

UCLASS()
class TOWERDEFENSE_API UTDTeslaAbility : public UTDTowerAbility
{
	GENERATED_BODY()

	virtual void AbilityEffect(AActor* HitActor) override;
};
