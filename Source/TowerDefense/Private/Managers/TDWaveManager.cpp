#include "Managers/TDWaveManager.h"

#include "Components/SplineComponent.h"
#include "Managers/TDMonsterSpline.h"
#include "Monsters/FMonsterWave.h"
#include "Monsters/TDMonster.h"

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
	
	FMonsterWave MonsterWave;
	RuntimeMonsterWaves.Dequeue(MonsterWave);
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SpawnMonster"), MonsterWave);
	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, TimerDelegate, MonsterWave.SpawnFrequency, true, MonsterWave.TimerBeforeSpawn);
}

void UTDWaveManager::SpawnMonster(FMonsterWave CurrentMonsterWave)
{
	FVector SpawnPosition = SplineManager->SplineComponent->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
	FRotator SpawnRotation = SplineManager->SplineComponent->GetRotationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
	FActorSpawnParameters SpawnParameters;
	TSubclassOf<ATDMonster> MonsterPrefab;
	
	float Total = 0;
	for(const auto& Monster : CurrentMonsterWave.SpawnProbabilities)
	{
		Total += Monster.SpawnProbability;
	}

	float RandomValue = FMath::RandRange(0.0f, Total);
	float CumulativeProbability = 0.0f;
	for (const auto& Monster : CurrentMonsterWave.SpawnProbabilities)
	{
		CumulativeProbability += Monster.SpawnProbability;
		if (RandomValue <= CumulativeProbability)
		{
			MonsterPrefab = Monster.MonsterClass;
			break;  
		}
	}

	if(!IsValid(MonsterPrefab))
	{
		UE_LOG(LogTemp, Error, TEXT("An element of a wave was empty"));
	}
	else
	{
		ATDMonster* Monster = GetWorld()->SpawnActor<ATDMonster>(MonsterPrefab, SpawnPosition, SpawnRotation, SpawnParameters);
		CurrentMonsters.Add(Monster);
		SplineManager->OnSplineMovementDelegate.AddDynamic(Monster, &ATDMonster::OnSplineMovement);
	}

	WaveMonsterCounter++;
	if(WaveMonsterCounter >= CurrentMonsterWave.NumberOfMonstersToSpawn)
	{
		GetWorld()->GetTimerManager().ClearTimer(WaveTimerHandle);
		WaveCounter++;
		WaveMonsterCounter = 0;
		if(WaveCounter % FMath::Max(BossWave.MaxNumOfWaveBeforeSpawn, 1)  == 0)
		{
			GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, this, &UTDWaveManager::SpawnBoss, BossWave.TimerBeforeSpawn);
			return;
		}
		else if(RuntimeMonsterWaves.IsEmpty())
		{
			UE_LOG(LogTemp, Warning, TEXT("LAST WAVE HAS SPAWNED"));
			return;
		}
		
		FMonsterWave MonsterWave;
		RuntimeMonsterWaves.Dequeue(MonsterWave);
	
		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("SpawnMonster"), MonsterWave);
		GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, TimerDelegate, MonsterWave.SpawnFrequency, true, MonsterWave.TimerBeforeSpawn);
	}
}

void UTDWaveManager::SpawnBoss()
{

	if(BossWave.BossClass !=nullptr)
	{
		FVector SpawnPosition = SplineManager->SplineComponent->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
		FRotator SpawnRotation = SplineManager->SplineComponent->GetRotationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
		FActorSpawnParameters SpawnParameters;
		
		ATDMonster* Monster = GetWorld()->SpawnActor<ATDMonster>(BossWave.BossClass, SpawnPosition, SpawnRotation, SpawnParameters);
		CurrentMonsters.Add(Monster);
		SplineManager->OnSplineMovementDelegate.AddDynamic(Monster, &ATDMonster::OnSplineMovement);
	}

	FMonsterWave MonsterWave;
	RuntimeMonsterWaves.Dequeue(MonsterWave);
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SpawnMonster"), MonsterWave);
	GetWorld()->GetTimerManager().SetTimer(WaveTimerHandle, TimerDelegate, MonsterWave.SpawnFrequency, true, MonsterWave.TimerBeforeSpawn);
}

void UTDWaveManager::OnMonsterDestroyed(ATDMonster* Monster)
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

TArray<ATDMonster*> UTDWaveManager::GetMonsters()
{
	TArray<ATDMonster*> Monsters;
	Monsters.Reserve(CurrentMonsters.Num());
	for(auto& Monster : CurrentMonsters)
	{
		Monsters.Add(Monster);
	}
	return  Monsters;
}
