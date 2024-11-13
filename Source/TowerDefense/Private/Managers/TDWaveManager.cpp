#include "Managers/TDWaveManager.h"

#include "Components/SplineComponent.h"
#include "Managers/TDMonsterSpline.h"
#include "Monsters/FMonsterWave.h"
#include "Monsters/TDMonster_Base.h"

UTDWaveManager::UTDWaveManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTDWaveManager::BeginPlay()
{
	Super::BeginPlay();
	RuntimeMonsterWaves.Empty();
	for(auto& Wave : EditorMonsterWaves)
	{
		RuntimeMonsterWaves.Enqueue(Wave);
	}
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&UTDWaveManager::SpawnMonster, TimeBeforeFirstWave, false);
}

void UTDWaveManager::SpawnMonster()
{
	FMonsterWave Wave;
	RuntimeMonsterWaves.Dequeue(Wave);

	FVector SpawnPosition = SplineManager->SplineComponent->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
	FRotator SpawnRotation = SplineManager->SplineComponent->GetRotationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
	FActorSpawnParameters SpawnParameters;
	
	ATDMonster_Base* Monster = GetWorld()->SpawnActor<ATDMonster_Base>(Wave.Monster, SpawnPosition, SpawnRotation, SpawnParameters);
	CurrentMonsters.Add(Monster);
	SplineManager->OnSplineMovementDelegate.AddDynamic(Monster, &ATDMonster_Base::OnSplineMovement);

	GetWorld()->GetTimerManager().ClearTimer(SpawnTimerHandle);
	
	if(!RuntimeMonsterWaves.IsEmpty())
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle,this,&UTDWaveManager::SpawnMonster, Wave.TimerBeforeNextWave, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Last Wave Has been Spawned"));
	}
}

void UTDWaveManager::OnMonsterDestroyed(ATDMonster_Base* Monster)
{
	if(CurrentMonsters.Contains(Monster))
	{
		CurrentMonsters.Remove(Monster);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("The Following Monster is not registered : %s"), *Monster->GetName());
	}
	Monster->Destroy();
}

TArray<ATDMonster_Base*> UTDWaveManager::GetMonsters()
{
	TArray<ATDMonster_Base*> Monsters;
	Monsters.Reserve(CurrentMonsters.Num());
	for(auto& Monster : CurrentMonsters)
	{
		Monsters.Add(Monster);
	}
	return  Monsters;
}
