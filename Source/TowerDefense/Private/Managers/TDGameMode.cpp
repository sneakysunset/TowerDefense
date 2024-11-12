#include "Managers/TDGameMode.h"

#include "Components/SplineComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/TDMonsterSpline.h"
#include "Managers/TDNexus.h"
#include "Monsters/TDMonster_Base.h"
#include "Blueprint/UserWidget.h"
#include "Widgets/TDMainUserWidget.h"

ATDGameMode::ATDGameMode()
{
}

void ATDGameMode::BeginPlay()
{
	Super::BeginPlay();
	CurrentGoldCount = StartGoldCount;

	SplineManager = Cast<ATDMonsterSpline>(UGameplayStatics::GetActorOfClass(GetWorld(), ATDMonsterSpline::StaticClass()));
	Nexus = Cast<ATDNexus>(UGameplayStatics::GetActorOfClass(GetWorld(), ATDNexus::StaticClass()));

	RuntimeMonsterWaves.Empty();
	for(auto& Wave : EditorMonsterWaves)
	{
		RuntimeMonsterWaves.Enqueue(Wave);
	}
	GetWorldTimerManager().SetTimer(SpawnTimerHandle,this,&ATDGameMode::SpawnMonster, TimeBeforeFirstWave, false);

	if(WidgetClass)
	{
		MainUserWidget = Cast<UTDMainUserWidget>(CreateWidget(GetWorld(), WidgetClass));
		if(MainUserWidget)
		{
			MainUserWidget->AddToViewport();
		}
	}
	
}

void ATDGameMode::SpawnMonster()
{
	FMonsterWave Wave;
	RuntimeMonsterWaves.Dequeue(Wave);

	FVector SpawnPosition = SplineManager->SplineComponent->GetLocationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
	FRotator SpawnRotation = SplineManager->SplineComponent->GetRotationAtDistanceAlongSpline(0, ESplineCoordinateSpace::Local);
	FActorSpawnParameters SpawnParameters;
	
	ATDMonster_Base* Monster = GetWorld()->SpawnActor<ATDMonster_Base>(Wave.Monster, SpawnPosition, SpawnRotation, SpawnParameters);
	CurrentMonsters.Add(Monster);
	SplineManager->OnSplineMovementDelegate.AddDynamic(Monster, &ATDMonster_Base::OnSplineMovement);

	GetWorldTimerManager().ClearTimer(SpawnTimerHandle);
	
	if(!RuntimeMonsterWaves.IsEmpty())
	{
		GetWorldTimerManager().SetTimer(SpawnTimerHandle,this,&ATDGameMode::SpawnMonster, Wave.TimerBeforeNextWave, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Last Wave Has been Spawned"));
	}
}

void ATDGameMode::OnHitNexus(ATDMonster_Base* Monster, int Damage)
{
	if(!Nexus->OnHit(Damage))
	{
		OnGameOver();
	}
	OnMonsterDestroyed(Monster);
}

void ATDGameMode::OnMonsterDestroyed(ATDMonster_Base* Monster)
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

void ATDGameMode::ChangeGoldCount(int Cost)
{
	CurrentGoldCount -= Cost;
	MainUserWidget->UpdateCost(CurrentGoldCount);
}

void ATDGameMode::OnGameOver()
{
}


