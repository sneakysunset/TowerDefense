#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Monsters/FMonsterWave.h"
#include "UObject/Object.h"
#include "Widgets/TDMainUserWidget.h"
#include "TDGameMode.generated.h"


class UTDMainUserWidget;
class ATDNexus;
class ATDMonster_Base;
class ATDMonsterSpline;
class ATDTower_Base;

UENUM(BlueprintType, Blueprintable)
enum class ETDEditMode : uint8
{
	ROTATE,
	DELETE,
	UPGRADE
};

UENUM(BlueprintType, Blueprintable)
enum class ETDTowerType : uint8
{
	SubmachineGun,
	Frost,
	Grenade,
	Tesla
};

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

private:
	UPROPERTY(EditAnywhere)
	int StartGoldCount;
	
	UPROPERTY(VisibleAnywhere)
	int CurrentGoldCount;
	
	UPROPERTY(EditAnywhere)
	float TimeBeforeFirstWave;
	
	UPROPERTY(EditAnywhere)
	TArray<FMonsterWave> EditorMonsterWaves;
	
	TQueue<FMonsterWave> RuntimeMonsterWaves;

	UPROPERTY(EditAnywhere)
	TMap<ETDTowerType, FTowerSpawn> TowerDictionary;

	UPROPERTY(VisibleAnywhere)
	ETDTowerType CurrentTowerSpawnType = ETDTowerType::SubmachineGun;

	UPROPERTY(VisibleAnywhere)
	ETDEditMode CurrentEditMode = ETDEditMode::ROTATE;
	
	UPROPERTY()
	TObjectPtr<ATDMonsterSpline> SplineManager;

	UPROPERTY()
	TObjectPtr<ATDNexus> Nexus;
	
	UPROPERTY()
	TSet<TObjectPtr<ATDMonster_Base>> CurrentMonsters;

	UPROPERTY()
	FTimerHandle SpawnTimerHandle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTDMainUserWidget> WidgetClass;

	UPROPERTY()
	TObjectPtr<UTDMainUserWidget> MainUserWidget;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void SpawnMonster();

	UFUNCTION()
	void OnGameOver();

	
public:
	UFUNCTION()
	void OnHitNexus(ATDMonster_Base* Monster, int Damage);

	UFUNCTION()
	void OnMonsterDestroyed(ATDMonster_Base* Monster);

	UFUNCTION()
	ETDEditMode GetEditMode(){return CurrentEditMode;}
	
	UFUNCTION(BlueprintCallable)
	void SetEditMode(ETDEditMode NewEditMode){CurrentEditMode = NewEditMode;}

	UFUNCTION()
	ETDTowerType GetCurrentTowerType(){return CurrentTowerSpawnType;}
	
	UFUNCTION(BlueprintCallable)
	void SetTowerType(ETDTowerType NewTowerType){CurrentTowerSpawnType = NewTowerType;}

	UFUNCTION()
	bool CanPurchaseTower(){return CurrentGoldCount >= TowerDictionary[CurrentTowerSpawnType].Cost;}

	UFUNCTION()
	bool CanPurchaseUpgrade(int UpgradeCost){return CurrentGoldCount >= UpgradeCost;}

	UFUNCTION()
	void PurchaseTower(){ ChangeGoldCount(TowerDictionary[CurrentTowerSpawnType].Cost);}

	UFUNCTION()
	void ChangeGoldCount(int Cost);

	UFUNCTION(BlueprintCallable)
	int GetGoldAmount(){return CurrentGoldCount;}
	
	UFUNCTION()
	TSubclassOf<ATDTower_Base> GetTowerPrefab(){return TowerDictionary[CurrentTowerSpawnType].TowerPrefab;}

	UFUNCTION(BlueprintCallable)
	int GetTowerCost(ETDTowerType TowerType){return TowerDictionary[TowerType].Cost;}

	UFUNCTION()
	void UpdateWidgetUpgradePrice(int NewUpgradePrice){MainUserWidget->UpdateUpgradePrice(NewUpgradePrice);}
};
