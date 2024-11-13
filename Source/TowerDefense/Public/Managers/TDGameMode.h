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
class ATDMonster_Base;
class ATDMonsterSpline;
class ATDTower_Base;

USTRUCT()
struct FTowerSpawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int Cost = 100;

	UPROPERTY(EditAnywhere)
	TSubclassOf<ATDTower_Base> TowerPrefab;
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
	TMap<ETDTowerType, FTowerSpawn> TowerDictionary;


protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameOver();
	
public:
	UFUNCTION()
	void OnHitNexus(ATDMonster_Base* Monster, int Damage);

	UFUNCTION()
	bool SpawnTower(FVector Position, AActor* TowerOwner, ATDTower_Base*& OutTower);
	
	UFUNCTION(BlueprintCallable)
	int GetTowerCost(ETDTowerType TowerType){return TowerDictionary[TowerType].Cost;}

	UFUNCTION()
	FTowerSpawn GetTowerSpawnParams(ETDTowerType TowerType){ return TowerDictionary[TowerType];}

	UFUNCTION(BlueprintCallable)
	void TriggerUpdateDebug();
};
