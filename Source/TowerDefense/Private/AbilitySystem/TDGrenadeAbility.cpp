#include "AbilitySystem/TDGrenadeAbility.h"

#include "AbilitySystem/TDAttributeData.h"
#include "Managers/TDGameMode.h"
#include "Managers/TDWaveManager.h"
#include "Monsters/TDMonster.h"

void UTDGrenadeAbility::AbilityEffect(AActor* HitActor)
{
	Super::AbilityEffect(HitActor);
	
	TArray<ATDMonster*> FoundMonsters = GameMode->WaveManager->GetMonsters();
	
	FVector GrenadeLocation = HitActor->GetActorLocation();

	for(auto& Monster : FoundMonsters)
	{
		float DistanceToMonster = FVector::Distance(GrenadeLocation, Monster->GetActorLocation());
		if(DistanceToMonster < AbilityStats.RadiusOfBlast)
		{
			Monster->AttributeData->ApplyAttributeChange(AbilityStats.AbilityMagnitude, AbilityStats.TargetAttribute,
				AbilityStats.AbilitySpeed, AbilityStats.Duration, AbilityStats.IsAdditive);
		}
	}
	DrawDebugSphere(GetWorld(), HitActor->GetActorLocation(), AbilityStats.RadiusOfBlast, 20, FColor::Red, false, .5f, 0, 5);
}
