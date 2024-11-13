#include "AbilitySystem/TDTowerAbility.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TDGameMode.h"
#include "Managers/TDWaveManager.h"
#include "Monsters/TDMonster_Base.h"

void UTDTowerAbility::Initialize(AActor* Outer, FTowerAbilityStats StatsOverride)
{
	Owner = Outer;
	AbilityStats = StatsOverride;
	GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->OnUpdateDebugsEvent.AddDynamic(this, &UTDTowerAbility::DrawDebugCone);
}

void UTDTowerAbility::ActivateAbility()
{
	float TimerRate = IsMonsterInRange || AbilityStats.IsActivatingWithNoMonsterInRange ? AbilityStats.Cooldown : AbilityStats.InactiveCheckForMonstersRate;
	GetWorld()->GetTimerManager().ClearTimer(ActivationTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(ActivationTimerHandle, this, &UTDTowerAbility::AbilityEffect, AbilityStats.Cooldown, true);
}

void UTDTowerAbility::AbilityEffect()
{
	TArray<ATDMonster_Base*> Monsters;
	if(GetMonstersInCone(Monsters) || AbilityStats.IsActivatingWithNoMonsterInRange)
	{
		if(!IsMonsterInRange)
		{
			IsMonsterInRange = true;
			ActivateAbility();
		}
	}
	else
	{
		if(IsMonsterInRange)
		{
			IsMonsterInRange = false;
			ActivateAbility();
			return;
		}
	}
}

void UTDTowerAbility::StopAbility()
{
	if(GetWorld()->GetTimerManager().IsTimerActive(ActivationTimerHandle))
	{
		GetWorld()->GetTimerManager().ClearTimer(ActivationTimerHandle);
	}
}

void UTDTowerAbility::PauseAbility(bool ToPause)
{
	if(ToPause && GetWorld()->GetTimerManager().IsTimerActive(ActivationTimerHandle))
	{
		GetWorld()->GetTimerManager().UnPauseTimer(ActivationTimerHandle);
	}
	else
	{
		GetWorld()->GetTimerManager().PauseTimer(ActivationTimerHandle);
	}
}

bool UTDTowerAbility::GetMonstersInCone(TArray<ATDMonster_Base*> OutMonsters) const
{
	TArray<ATDMonster_Base*> FoundMonsters = GameMode->WaveManager->GetMonsters();
	OutMonsters.Reserve(FoundMonsters.Num());
	
	FVector TowerLocation = Owner->GetActorLocation();
	FVector TowerForward = Owner->GetActorForwardVector();

	for(auto& Monster : FoundMonsters)
	{
		float DistanceToMonster = FVector::Distance(TowerLocation, Monster->GetActorLocation());
		if(DistanceToMonster > AbilityStats.Range)
		{
			continue;
		}
		
		FVector DirectionToMonster = (Monster->GetActorLocation() - TowerLocation).GetSafeNormal();
		float AngleToMonster = FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(TowerForward, DirectionToMonster)));
		if (AngleToMonster <= AbilityStats.ConeAngle)
		{
			OutMonsters.Add(Cast<ATDMonster_Base>(Monster));
		}
	}
	OutMonsters.Shrink();
	return OutMonsters.Num() > 0;
}

void UTDTowerAbility::DrawDebugCone()
{
	FColor DebugColor = FColor::Blue.WithAlpha(100);
	DrawDebugCircleArc(GetWorld(), Owner->GetActorLocation(), AbilityStats.Range, Owner->GetActorForwardVector(), AbilityStats.ConeAngle, 8, DebugColor,true);
} 
