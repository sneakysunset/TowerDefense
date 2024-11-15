#pragma once

#include "CoreMinimal.h"
#include "Monsters/FMonsterWave.h"
#include "Components/ActorComponent.h"
#include "TDWaveManager.generated.h"


class ATDMonsterSpline;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDWaveManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDWaveManager();
	
private :
	UPROPERTY(EditAnywhere)
	TArray<FMonsterWave> EditorMonsterWaves;
	
	TQueue<FMonsterWave> RuntimeMonsterWaves;
	
	UPROPERTY()
	TSet<TObjectPtr<ATDMonster>> CurrentMonsters;

	FTimerHandle WaveTimerHandle;

	UPROPERTY()
	TObjectPtr<ATDMonsterSpline> SplineManager;
	
	UPROPERTY()
	int WaveMonsterCounter;

	UPROPERTY()
	int WaveCounter;

	UPROPERTY(EditAnywhere)
	FBossWave BossWave;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnMonster(FMonsterWave CurrentMonsterWave);

	UFUNCTION()
	void SpawnBoss();
	
public:
	UFUNCTION()
	void OnMonsterDestroyed(ATDMonster* Monster);

	UFUNCTION()
	void SetSplineManager(ATDMonsterSpline* InSplineManager){SplineManager = InSplineManager;}

	UFUNCTION()
	TArray<ATDMonster*> GetMonsters();
};
