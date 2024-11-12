#pragma once

#include"FMonsterWave.generated.h"

class ATDMonster_Base;

USTRUCT()
struct FMonsterWave
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDMonster_Base> Monster;

	UPROPERTY(EditAnywhere)
	float TimerBeforeNextWave = 1;
};
