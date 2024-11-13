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
	return CurrentGoldCount >= OwningGameMode->GetTowerSpawnParams(CurrentTowerType).Cost;
}

bool UTDGoldManager::CanPurchaseUpgrade(int UpgradeCost)
{
	return CurrentGoldCount >= UpgradeCost;
}

void UTDGoldManager::PurchaseTower()
{
	auto CurrentTowerType = OwningGameMode->MainWidgetManager->GetCurrentTowerSpawnType();
	ChangeGoldCount(OwningGameMode->GetTowerSpawnParams(CurrentTowerType).Cost);
}

void UTDGoldManager::ChangeGoldCount(int Cost)
{
	CurrentGoldCount -= Cost;
	OwningGameMode->MainWidgetManager->MainUserWidget->UpdateCost(CurrentGoldCount);
}
