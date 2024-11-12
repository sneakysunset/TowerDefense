#include "Managers/TDWaveManager.h"

UTDWaveManager::UTDWaveManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTDWaveManager::BeginPlay()
{
	Super::BeginPlay();
}