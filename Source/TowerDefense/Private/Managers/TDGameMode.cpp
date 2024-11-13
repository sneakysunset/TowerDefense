#include "Managers/TDGameMode.h"

#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TDMonsterSpline.h"
#include "Managers/TDNexus.h"
#include "Monsters/TDMonster_Base.h"
#include "Blueprint/UserWidget.h"
#include "Managers/TDGoldManager.h"
#include "Managers/TDWaveManager.h"
#include "Towers/TDTower_Base.h"
#include "Widgets/TDMainUserWidget.h"

ATDGameMode::ATDGameMode()
{
	WaveManager = CreateDefaultSubobject<UTDWaveManager>(TEXT("Wave Manager"));
	MainWidgetManager = CreateDefaultSubobject<UTDWidgetManager>(TEXT("Widget Manager"));
	GoldManager = CreateDefaultSubobject<UTDGoldManager>(TEXT("Gold Manager"));
}

void ATDGameMode::BeginPlay()
{
	Super::BeginPlay();

	SplineManager = Cast<ATDMonsterSpline>(UGameplayStatics::GetActorOfClass(GetWorld(), ATDMonsterSpline::StaticClass()));
	Nexus = Cast<ATDNexus>(UGameplayStatics::GetActorOfClass(GetWorld(), ATDNexus::StaticClass()));
	WaveManager->SetSplineManager(SplineManager);
	GoldManager->OnStart();
	MainWidgetManager->MainUserWidget->OnBeginPlay();
}

void ATDGameMode::OnHitNexus(ATDMonster_Base* Monster, int Damage)
{
	if(!Nexus->OnHit(Damage))
	{
		OnGameOver();
	}
	WaveManager->OnMonsterDestroyed(Monster);
}

 bool ATDGameMode::SpawnTower(FVector Position, AActor* TowerOwner, ATDTower_Base* OutTower)
{
	auto TowerParams = GetTowerSpawnParams(MainWidgetManager->GetCurrentTowerSpawnType());
	if(TowerParams.TowerPrefab == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Tower Subclass is nullptr"));
		return false;
	}
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = TowerOwner;
	OutTower = GetWorld()->SpawnActor<ATDTower_Base>(TowerParams.TowerPrefab, Position,  FRotator::ZeroRotator, SpawnParameters);

	GoldManager->PurchaseTower();
	TriggerUpdateDebug();
	return true;
}

void ATDGameMode::TriggerUpdateDebug()
{
	FlushPersistentDebugLines(GetWorld());
	if(OnUpdateDebugsEvent.IsBound())
	{
		OnUpdateDebugsEvent.Broadcast();
	}
}

void ATDGameMode::OnGameOver()
{
}


