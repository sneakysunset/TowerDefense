#pragma once

#include "CoreMinimal.h"
#include "TDWidgetManager.h"
#include "GameFramework/GameModeBase.h"
#include "Monsters/FMonsterWave.h"
#include "UObject/Object.h"
#include "Widgets/TDMainUserWidget.h"
#include "TDGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUpdateDebugs);

class UTDGoldManager;
class UTDWidgetManager;
class UTDWaveManager;
class ATDNexus;
class ATDMonster;
class ATDMonsterSpline;
class ATDTower;

USTRUCT()
struct FTowerSpawnParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int Cost;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDTower> TowerPrefab;
};

UCLASS()
class TOWERDEFENSE_API ATDGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATDGameMode();

	FOnUpdateDebugs OnUpdateDebugsEvent;
	
	UPROPERTY()
	TObjectPtr<ATDMonsterSpline> SplineManager;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UTDWaveManager> WaveManager;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess), BlueprintReadWrite)
	TObjectPtr<UTDWidgetManager> MainWidgetManager;

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess), BlueprintReadWrite)
	TObjectPtr<UTDGoldManager> GoldManager;
	
	UPROPERTY()
	TObjectPtr<ATDNexus> Nexus;
	
private:
	UPROPERTY(EditAnywhere)
	TMap<ETDTowerType, FTowerSpawnParams> TowerCostDictionary;


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameOver();
	
public:
	UFUNCTION()
	void OnHitNexus(ATDMonster* Monster, int Damage);
	
	UFUNCTION(BlueprintCallable)
	int GetTowerCost(ETDTowerType TowerType){return TowerCostDictionary.Contains(TowerType) ? TowerCostDictionary[TowerType].Cost : 0;}

	UFUNCTION(BlueprintCallable)
	int GetCurrentTowerCost(){return TowerCostDictionary.Contains(MainWidgetManager->CurrentTowerSpawnType) ?
		TowerCostDictionary[MainWidgetManager->CurrentTowerSpawnType].Cost : 0;}
	
	UFUNCTION(BlueprintCallable)
	TSubclassOf<ATDTower> GetCurrentTowerPrefab(){return TowerCostDictionary.Contains(MainWidgetManager->CurrentTowerSpawnType) ?
		TowerCostDictionary[MainWidgetManager->CurrentTowerSpawnType].TowerPrefab: 0;}

	UFUNCTION(BlueprintCallable)
	void TriggerUpdateDebug();
};
