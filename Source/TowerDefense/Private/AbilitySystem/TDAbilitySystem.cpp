
#include "AbilitySystem/TDAbilitySystem.h"

#include "AbilitySystem/TDTowerAbility.h"

UTDAbilitySystem::UTDAbilitySystem()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTDAbilitySystem::BeginPlay()
{
	Super::BeginPlay();
	if(!IsValid(AbilityClass))
	{
		UE_LOG(LogTemp, Error, TEXT("No Tower Subclass Selected in Ability System"));
		return;
	}
	TowerAbility = NewObject<UTDTowerAbility>(this, AbilityClass);
	TowerAbility->Initialize(GetOwner(), AbilityStatsOverride);
}



