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
	float TimeBeforeFirstWave;
	
	UPROPERTY(EditAnywhere)
	TArray<FMonsterWave> EditorMonsterWaves;
	
	TQueue<FMonsterWave> RuntimeMonsterWaves;
	
	UPROPERTY()
	TSet<TObjectPtr<ATDMonster_Base>> CurrentMonsters;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UPROPERTY()
	TObjectPtr<ATDMonsterSpline> SplineManager;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnMonster();

public:
	UFUNCTION()
	void OnMonsterDestroyed(ATDMonster_Base* Monster);

	UFUNCTION()
	void SetSplineManager(ATDMonsterSpline* InSplineManager){SplineManager = InSplineManager;}

	UFUNCTION()
	TArray<ATDMonster_Base*> GetMonsters();
};
