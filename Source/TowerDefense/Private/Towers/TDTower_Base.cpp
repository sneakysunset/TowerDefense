#include "Towers/TDTower_Base.h"

#include <Windows.ApplicationModel.Activation.h>

#include "AbilitySystem/TDAbilitySystem.h"
#include "Managers/TDGameMode.h"
#include "Managers/TDGoldManager.h"
#include "Towers/TDTowerSlot.h"
#include "Managers/TDWidgetManager.h"

ATDTower_Base::ATDTower_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	AbilitySystem = CreateDefaultSubobject<UTDAbilitySystem>("Ability System");
	RootComponent = MeshComponent;
}

void ATDTower_Base::BeginPlay()
{
	Super::BeginPlay();
	NormalMaterial = MeshComponent->GetMaterial(0);
	CurrentGameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
	
}

void ATDTower_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATDTower_Base::OnStartHover()
{
	auto Material = CurrentGameMode->GoldManager->CanPurchaseUpgrade(UpgradeCost)? HighlightedMaterial : HighlightNotEnoughGoldMaterial;
	MeshComponent->SetMaterial(0, Material);
	CurrentGameMode->MainWidgetManager->UpdateWidgetUpgradePrice(UpgradeCost);
}

void ATDTower_Base::OnStopHover()
{
	MeshComponent->SetMaterial(0, NormalMaterial);
	CurrentGameMode->MainWidgetManager->UpdateWidgetUpgradePrice(0);
}

void ATDTower_Base::OnClick()
{
	FRotator NewRotation = GetActorRotation();
	switch(CurrentGameMode->MainWidgetManager->GetEditMode())
	{
	case ETDEditMode::ROTATE:
		NewRotation.Yaw += 90;
		SetActorRotation(NewRotation);
		break;
	case ETDEditMode::DELETE_TOWER:
		Destroy();
		break;
	case ETDEditMode::UPGRADE:
		if(!CurrentGameMode->GoldManager->CanPurchaseUpgrade(UpgradeCost))
		{
			return;
		}

		UpgradeTower();
		CurrentGameMode->GoldManager->ChangeGoldCount(UpgradeCost);
		break;
	}
}

void ATDTower_Base::Destroyed()
{
	Super::Destroyed();
	OnDestructionEvent.Execute();
}

void ATDTower_Base::UpgradeTower()
{
}

