#include "TDTeslaAbility.h"
#include "AbilitySystem/TDAttributeData.h"
#include "Monsters/TDMonster.h"

void UTDTeslaAbility::AbilityEffect(AActor* HitActor)
{
	Super::AbilityEffect(HitActor);

	TArray<ATDMonster*> Monsters;
	GetMonstersInCone(Monsters);
	if(Monsters.Num() == 0) return;
	DrawDebugLine(GetWorld(), Owner->GetActorLocation(), Monsters[0]->GetActorLocation(), FColor::White, false, AbilityStats.Cooldown, 10, 5);
	for(int i = 0; i < FMath::Min(AbilityStats.NumberOfRiples, Monsters.Num()); i++)
	{
		Monsters[i]->AttributeData->ApplyAttributeChange(AbilityStats.AbilityMagnitude, AbilityStats.TargetAttribute,
				AbilityStats.AbilitySpeed, AbilityStats.Duration, AbilityStats.IsAdditive);
		if(i == Monsters.Num() - 1)
			break;
		DrawDebugLine(GetWorld(), Monsters[i]->GetActorLocation(), Monsters[i + 1]->GetActorLocation(), FColor::White, false, AbilityStats.Cooldown, 10, 5);
	}
}
