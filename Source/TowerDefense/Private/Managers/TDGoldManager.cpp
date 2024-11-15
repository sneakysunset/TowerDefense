#include "Managers/TDGoldManager.h"

#include "Managers/TDGameMode.h"

UTDGoldManager::UTDGoldManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTDGoldManager::OnStart()
{
	OwningGameMode = Cast<ATDGameMode>(GetOwner());
	CurrentGoldCount = StartGoldCount;
}

bool UTDGoldManager::CanPurchaseTower()
{
	auto CurrentTowerType = OwningGameMode->MainWidgetManager->GetCurrentTowerSpawnType();
	return CurrentGoldCount >= OwningGameMode->GetTowerCost(CurrentTowerType);
}

bool UTDGoldManager::CanPurchaseUpgrade(int UpgradeCost)
{
	return CurrentGoldCount >= UpgradeCost;
}

void UTDGoldManager::PurchaseTower()
{
	auto CurrentTowerType = OwningGameMode->MainWidgetManager->GetCurrentTowerSpawnType();
	ChangeGoldCount(-OwningGameMode->GetTowerCost(CurrentTowerType));
}

void UTDGoldManager::ChangeGoldCount(int Cost)
{
	CurrentGoldCount += Cost;
	OwningGameMode->MainWidgetManager->MainUserWidget->UpdateCost(CurrentGoldCount);
}
