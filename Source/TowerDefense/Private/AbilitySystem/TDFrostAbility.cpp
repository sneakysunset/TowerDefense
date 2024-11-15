#include "AbilitySystem/TDFrostAbility.h"
#include "AbilitySystem/TDAttributeData.h"
#include "Monsters/TDMonster.h"

void UTDFrostAbility::AbilityEffect(AActor* HitActor)
{
	Super::AbilityEffect(HitActor);

	TArray<ATDMonster*> Monsters;
	GetMonstersInCone(Monsters);

	for(auto Monster : Monsters)
	{
		Monster->AttributeData->ApplyAttributeChange
			(AbilityStats.AbilityMagnitude, AbilityStats.TargetAttribute,
			AbilityStats.AbilitySpeed, AbilityStats.Duration, AbilityStats.IsAdditive);
	}
	DrawDebugSphere(GetWorld(), Owner->GetActorLocation(), AbilityStats.Range, 20, FColor::Cyan, false, .5f, 0, 5);
}
