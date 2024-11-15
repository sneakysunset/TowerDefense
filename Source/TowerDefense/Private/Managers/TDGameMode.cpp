#include "Managers/TDGameMode.h"

#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TDMonsterSpline.h"
#include "Managers/TDNexus.h"
#include "Monsters/TDMonster.h"
#include "Blueprint/UserWidget.h"
#include "Managers/TDGoldManager.h"
#include "Managers/TDWaveManager.h"
#include "Towers/TDTower.h"
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

void ATDGameMode::OnHitNexus(ATDMonster* Monster, int Damage)
{
	if(!Nexus->OnHit(Damage))
	{
		OnGameOver();
	}
	WaveManager->OnMonsterDestroyed(Monster);
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


