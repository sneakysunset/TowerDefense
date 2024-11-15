#include "Managers/TDNexus.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TDGameMode.h"
#include "Managers/TDWaveManager.h"
#include "Managers/TDMonsterSpline.h"
#include "Monsters/TDMonster.h"

ATDNexus::ATDNexus()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
}

void ATDNexus::BeginPlay()
{
	Super::BeginPlay();
	CurrentNexusHealthPoints = StartNexusHealthPoints;
}

void ATDNexus::OnGameOver()
{
	Destroy();
}

bool ATDNexus::OnHit(int Damage)
{
	CurrentNexusHealthPoints -= Damage;
	Cast<ATDGameMode>(GetWorld()->GetAuthGameMode())->MainWidgetManager->UpdateWidgetNexusHP(float(CurrentNexusHealthPoints) / float(StartNexusHealthPoints));
	if(CurrentNexusHealthPoints <= 0)
	{
		OnGameOver();
		return false;
	}
	return true;
}


