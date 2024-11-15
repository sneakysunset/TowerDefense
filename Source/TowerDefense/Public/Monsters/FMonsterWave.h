#pragma once

#include"FMonsterWave.generated.h"

class ATDMonster;

USTRUCT()
struct FWeightedMonster
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDMonster> MonsterClass;

	UPROPERTY(EditAnywhere)
	float SpawnProbability;
};

USTRUCT()
struct FMonsterWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FWeightedMonster> SpawnProbabilities;

	UPROPERTY(EditAnywhere)
	int NumberOfMonstersToSpawn;
	
	UPROPERTY(EditAnywhere)
	float SpawnFrequency;
	
	UPROPERTY(EditAnywhere)
	float TimerBeforeSpawn;
};

USTRUCT()
struct FBossWave
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int MaxNumOfWaveBeforeSpawn;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDMonster> BossClass;

	UPROPERTY(EditAnywhere)
	float TimerBeforeSpawn;
};