#include "Towers/TDTowerSlot.h"

#include "Managers/TDGameMode.h"
#include "Managers/TDGoldManager.h"
#include "Towers/TDTower.h"

ATDTowerSlot::ATDTowerSlot()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
}

void ATDTowerSlot::BeginPlay()
{
	Super::BeginPlay();
	NormalMaterial = MeshComponent->GetMaterial(0);
	CurrentGameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
}

void ATDTowerSlot::OnStartHover()
{
	if(CurrentTower != nullptr) return;
	auto Material = CurrentGameMode->GoldManager->CanPurchaseTower() ? HighlightedMaterial : HighlightNotEnoughGoldMaterial;
	MeshComponent->SetMaterial(0, Material);
}

void ATDTowerSlot::OnStopHover()
{
	MeshComponent->SetMaterial(0, NormalMaterial);
}

void ATDTowerSlot::OnClick()
{
	if(CurrentTower != nullptr || !CurrentGameMode->GoldManager->CanPurchaseTower()) return;
	
	FVector SpawnPosition = GetActorLocation() + FVector(0,0,50);
	TSubclassOf<ATDTower> TowerPrefab = CurrentGameMode->GetCurrentTowerPrefab();
	if(!IsValid(TowerPrefab))
	{
		UE_LOG(LogTemp, Error, TEXT("Tower Subclass is nullptr"));
		return ;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	CurrentTower = GetWorld()->SpawnActor<ATDTower>(TowerPrefab, SpawnPosition,  FRotator::ZeroRotator, SpawnParameters);
	
	
	CurrentGameMode->GoldManager->PurchaseTower();
	CurrentTower->OnDestructionEvent.BindDynamic(this, &ATDTowerSlot::OnTowerDestroyed);
	
	OnStopHover();
}




