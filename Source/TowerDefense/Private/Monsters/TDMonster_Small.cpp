#include "Monsters/TDMonster_Small.h"

ATDMonster_Small::ATDMonster_Small()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATDMonster_Small::BeginPlay()
{
	Super::BeginPlay();
}

void ATDMonster_Small::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

