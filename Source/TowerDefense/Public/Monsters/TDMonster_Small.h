// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TDMonster_Base.h"
#include "TDMonster_Small.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDMonster_Small : public ATDMonster_Base
{
	GENERATED_BODY()

public:
	ATDMonster_Small();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
