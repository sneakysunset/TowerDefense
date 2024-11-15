#include "Towers/TDTower.h"

#include <IVectorChangedEventArgs.h>

#include "AbilitySystem/TDAbilitySystem.h"
#include "AbilitySystem/TDTowerAbility.h"
#include "Managers/TDGameMode.h"
#include "Managers/TDGoldManager.h"
#include "Towers/TDTowerSlot.h"
#include "Managers/TDWidgetManager.h"

ATDTower::ATDTower()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	AbilitySystem = CreateDefaultSubobject<UTDAbilitySystem>("Ability System");
	RootComponent = MeshComponent;
}

void ATDTower::BeginPlay()
{
	Super::BeginPlay();
	NormalMaterial = MeshComponent->GetMaterial(0);
	CurrentGameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
}

void ATDTower::OnStartHover()
{
	bool bConditionUpgrade = CurrentGameMode->MainWidgetManager->CurrentEditMode != ETDEditMode::UPGRADE
	||	(CurrentGameMode->GoldManager->CanPurchaseUpgrade(AbilitySystem->GetUpgradePrice())
	&& !AbilitySystem->IsTowerAtMaxLevel());

	auto Material = bConditionUpgrade ? HighlightedMaterial : HighlightNotEnoughGoldMaterial;
	MeshComponent->SetMaterial(0, Material);
	CurrentGameMode->MainWidgetManager->UpdateWidgetUpgradePrice(AbilitySystem->GetUpgradePrice());
}

void ATDTower::OnStopHover()
{
	MeshComponent->SetMaterial(0, NormalMaterial);
	CurrentGameMode->MainWidgetManager->UpdateWidgetUpgradePrice(0);
}

void ATDTower::OnClick()
{
	FRotator NewRotation = GetActorRotation();
	switch(CurrentGameMode->MainWidgetManager->GetEditMode())
	{
	case ETDEditMode::ROTATE:
		NewRotation.Yaw += 90;
		SetActorRotation(NewRotation);
		CurrentGameMode->TriggerUpdateDebug();
		break;
	case ETDEditMode::DELETE_TOWER:
		Destroy();
		AbilitySystem->MarkAsDestroyed();
		CurrentGameMode->TriggerUpdateDebug();
		break;
	case ETDEditMode::UPGRADE:
		if(!CurrentGameMode->GoldManager->CanPurchaseUpgrade(AbilitySystem->GetUpgradePrice()) || AbilitySystem->IsTowerAtMaxLevel())
		{
			return;
		}

		AbilitySystem->UpgradeTower();
		CurrentGameMode->GoldManager->ChangeGoldCount(-AbilitySystem->GetUpgradePrice());
		CurrentGameMode->TriggerUpdateDebug();
		break;
	}
}

void ATDTower::Destroyed()
{
	Super::Destroyed();
	OnDestructionEvent.ExecuteIfBound();
}
