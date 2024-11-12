#include "Towers/TDTowerSlot.h"

#include "Managers/TDGameMode.h"
#include "Towers/TDTower_Base.h"

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
	auto Material = CurrentGameMode->CanPurchaseTower() ? HighlightedMaterial : HighlightNotEnoughGoldMaterial;
	MeshComponent->SetMaterial(0, Material);
}

void ATDTowerSlot::OnStopHover()
{
	MeshComponent->SetMaterial(0, NormalMaterial);
}

void ATDTowerSlot::OnClick()
{
	if(CurrentTower != nullptr || !CurrentGameMode->CanPurchaseTower()) return;
 	TSubclassOf<ATDTower_Base> TowerPrefab = CurrentGameMode->GetTowerPrefab();
	FVector SpawnPosition = GetActorLocation() + FVector(0,0,50);
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	
	CurrentTower = GetWorld()->SpawnActor<ATDTower_Base>(TowerPrefab, SpawnPosition, FRotator::ZeroRotator, SpawnParameters);
	CurrentGameMode->PurchaseTower();

	CurrentTower->OnDestructionEvent.BindDynamic(this, &ATDTowerSlot::OnTowerDestroyed);
	
	OnStopHover();
}




