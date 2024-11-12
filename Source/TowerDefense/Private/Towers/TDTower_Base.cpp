#include "Towers/TDTower_Base.h"
#include "Managers/TDGameMode.h"
#include "Towers/TDTowerSlot.h"


ATDTower_Base::ATDTower_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
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
	auto Material = CurrentGameMode->CanPurchaseUpgrade(UpgradeCost)? HighlightedMaterial : HighlightNotEnoughGoldMaterial;
	MeshComponent->SetMaterial(0, Material);
	CurrentGameMode->UpdateWidgetUpgradePrice(UpgradeCost);
}

void ATDTower_Base::OnStopHover()
{
	MeshComponent->SetMaterial(0, NormalMaterial);
	CurrentGameMode->UpdateWidgetUpgradePrice(0);
}

void ATDTower_Base::OnClick()
{
	FRotator NewRotation = GetActorRotation();
	switch(CurrentGameMode->GetEditMode())
	{
	case ETDEditMode::ROTATE:
		NewRotation.Yaw += 90;
		SetActorRotation(NewRotation);
		break;
	case ETDEditMode::DELETE:
		Destroy();
		break;
	case ETDEditMode::UPGRADE:
		if(!CurrentGameMode->CanPurchaseUpgrade(UpgradeCost))
		{
			return;
		}

		UpgradeTower();
		CurrentGameMode->ChangeGoldCount(UpgradeCost);
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

