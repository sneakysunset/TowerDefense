#include "AbilitySystem/TDTowerAbility.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TDGameMode.h"
#include "Managers/TDWaveManager.h"
#include "Monsters/TDMonster.h"
#include "Towers/TDTowerProjectile.h"

void UTDTowerAbility::Initialize(AActor* Outer, FTowerAbilityStats StatsOverride)
{
	Owner = Outer;
	AbilityStats = StatsOverride;
	GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
	GameMode->OnUpdateDebugsEvent.AddDynamic(this, &UTDTowerAbility::DrawDebugCone);
	GameMode->TriggerUpdateDebug();
	ActivateAbility();
}

void UTDTowerAbility::ActivateAbility()
{
	float FirstIterationCooldown = GetWorld()->GetTimerManager().IsTimerActive(ActivationTimerHandle) ?
		AbilityStats.Cooldown : AbilityStats.Cooldown - GetWorld()->GetTimerManager().GetTimerElapsed(ActivationTimerHandle);
	GetWorld()->GetTimerManager().ClearTimer(ActivationTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(ActivationTimerHandle, this, &UTDTowerAbility::OnAbilityTriggered, AbilityStats.Cooldown, true, FirstIterationCooldown);
}

void UTDTowerAbility::OnAbilityTriggered()
{
	
	if(AbilityStats.IsUsingProjectiles)
	{
		TArray<ATDMonster*> Monsters;
		if(!GetMonstersInCone(Monsters))
		{
			return;
		}
		FVector SpawnPosition = Owner->GetActorLocation() + Owner->GetActorForwardVector() + FVector(0, 0, 200);
		FVector Direction = (Monsters[0]->GetActorLocation() - SpawnPosition).GetSafeNormal();
		Direction.Z = 0;
		FRotator SpawnRotation = Direction.Rotation();
		FActorSpawnParameters SpawnParams;
		ATDTowerProjectile* Projectile =  GetWorld()->SpawnActor<ATDTowerProjectile>(AbilityStats.ProjectileClass, SpawnPosition, SpawnRotation, SpawnParams);
		Projectile->Initialize(AbilityStats.ProjectileSpeed, Monsters[0]);
		Projectile->OnProjectileHitEvent.BindDynamic(this, &UTDTowerAbility::OnProjectileHit);
	}
	else
	{
		AbilityEffect();
	}
}

void UTDTowerAbility::OnProjectileHit(AActor* HitActor)
{
	AbilityEffect(HitActor);
}

void UTDTowerAbility::AbilityEffect(AActor* HitActor)
{
}

bool UTDTowerAbility::GetMonstersInCone(TArray<ATDMonster*>& OutMonsters) const
{
	TArray<ATDMonster*> FoundMonsters = GameMode->WaveManager->GetMonsters();
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
		if (AngleToMonster <= AbilityStats.ConeAngle / 2)
		{
			OutMonsters.Add(Cast<ATDMonster>(Monster));
		}
	}
	OutMonsters.Shrink();
	if(OutMonsters.Num() == 0) return false;
	if(AbilityStats.SortingType != ETDAbilitySortingType::NONE)
	{
		Algo::Sort(OutMonsters, [this](const ATDMonster* m1, const ATDMonster* m2)
		{
			switch(AbilityStats.SortingType)
			{
			case ETDAbilitySortingType::ClosestMonster:
				return FVector::Distance(Owner->GetActorLocation(), m1->GetActorLocation()) < FVector::Distance(Owner->GetActorLocation(), m2->GetActorLocation());
			case ETDAbilitySortingType::FurthestMonster:
				return FVector::Distance(Owner->GetActorLocation(), m1->GetActorLocation()) > FVector::Distance(Owner->GetActorLocation(), m2->GetActorLocation());
			case ETDAbilitySortingType::MostProgressOnPath:
				return m1->GetProgress() > m2->GetProgress();
			case ETDAbilitySortingType::LeastProgressOnPath:
				return m1->GetProgress() < m2->GetProgress();
			}
			return false;
		});
		//DrawDebugLine(GetWorld(), Owner->GetActorLocation(), OutMonsters[0]->GetActorLocation(), FColor::Red, false, 1, 0, 10);
	}
	return true;

	for(int i = 1; i < OutMonsters.Num(); i++)
	{
		DrawDebugLine(GetWorld(), Owner->GetActorLocation(), OutMonsters[i]->GetActorLocation(), FColor::Black, false, 1, 0, 5);
	}
}

void UTDTowerAbility::UpdateStats(FTowerAbilityStats StatsOverride)
{
	UE_LOG(LogTemp, Warning, TEXT("stats are upgrades"))
	AbilityStats = StatsOverride;
}

void UTDTowerAbility::DrawDebugCone()
{
	if(IsMarkedAsDeleted)
		return;
		
	FColor DebugColor = FColor::Blue.WithAlpha(100);
	float HalfWidth = AbilityStats.ConeAngle / 2.0f;
	int32 NumberOfSegments = 20;
	
	FVector PreviousPoint =  Owner->GetActorLocation();
	for(int i = 0; i < NumberOfSegments; i++)
	{
		FRotator Rotation(0, -HalfWidth + (i * AbilityStats.ConeAngle / (NumberOfSegments - 1)), 0);
		FVector EndPoint = Owner->GetActorLocation() + Rotation.RotateVector(Owner->GetActorForwardVector() * AbilityStats.Range);
		PreviousPoint = AbilityStats.ConeAngle > 355 && i == 0 ? EndPoint : PreviousPoint;
		DrawDebugLine(GetWorld(), PreviousPoint, EndPoint, DebugColor, true, -1, 0, 15);
		PreviousPoint = EndPoint;
	}
	if(AbilityStats.ConeAngle <= 355)
	{
		DrawDebugLine(GetWorld(), PreviousPoint, Owner->GetActorLocation(), DebugColor, true, -1, 0, 15);
	}
} 
