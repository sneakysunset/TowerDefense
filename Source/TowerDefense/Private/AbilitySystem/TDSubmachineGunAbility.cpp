#include "AbilitySystem/TDSubmachineGunAbility.h"

#include "AbilitySystem/TDAttributeData.h"
#include "Monsters/TDMonster.h"

void UTDSubmachineGunAbility::AbilityEffect(AActor* HitActor)
{
	Super::AbilityEffect(HitActor);
	UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *HitActor->GetName());
	if(auto Monster = Cast<ATDMonster>(HitActor))
	{

		Monster->AttributeData->ApplyAttributeChange(AbilityStats.AbilityMagnitude, AbilityStats.TargetAttribute);
	}
}
