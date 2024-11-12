#include "Managers/TDNexus.h"

ATDNexus::ATDNexus()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = MeshComponent;
}

void ATDNexus::BeginPlay()
{
	Super::BeginPlay();
}

void ATDNexus::OnGameOver()
{
	Destroy();
}

bool ATDNexus::OnHit(int Damage)
{
	CurrentNexusHealthPoints -= Damage;
	if(CurrentNexusHealthPoints <= 0)
	{
		OnGameOver();
		return false;
	}
	return true;
}


