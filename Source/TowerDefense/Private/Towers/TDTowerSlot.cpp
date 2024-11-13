#include "Towers/TDTowerSlot.h"

#include "Managers/TDGameMode.h"
#include "Managers/TDGoldManager.h"
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
	ATDTower_Base* NewTowerBase = nullptr;
 	if(!CurrentGameMode->SpawnTower(SpawnPosition, this, NewTowerBase))
 	{
 		return;
 	}
	CurrentTower = NewTowerBase;
	CurrentTower->OnDestructionEvent.BindDynamic(this, &ATDTowerSlot::OnTowerDestroyed);
	
	OnStopHover();
}




