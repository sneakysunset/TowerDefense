#include "Monsters/TDMonster.h"

#include "AbilitySystem/TDAttributeData.h"
#include "AbilitySystem/TDTowerAbility.h"
#include "Components/SplineComponent.h"
#include "Managers/TDGameMode.h"
#include "Managers/TDGoldManager.h"
#include "Managers/TDWaveManager.h"

ATDMonster::ATDMonster()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	AttributeData = CreateDefaultSubobject<UTDAttributeData>(TEXT("Attributes"));

	AttributeData->AttributeMap.Add(ETDAttributeType::Damage);
	AttributeData->AttributeMap.Add(ETDAttributeType::Health);
	AttributeData->AttributeMap.Add(ETDAttributeType::Speed);
	RootComponent = MeshComponent;
}

void ATDMonster::BeginPlay()
{
	Super::BeginPlay();
	StartMaterial = MeshComponent->GetMaterial(0);
	AttributeData->OnAttributeUpdateDelegate.BindDynamic(this, &ATDMonster::OnAttributeUpdateEvent);
}

void ATDMonster::OnSplineMovement(USplineComponent* Spline, float DeltaTime)
{
	float MovementDelta = AttributeData->AttributeMap[ETDAttributeType::Speed] * DeltaTime;
	SplineProgress += MovementDelta;
	if(SplineProgress >= Spline->GetSplineLength())
	{
		Cast<ATDGameMode>(GetWorld()->GetAuthGameMode())->OnHitNexus(this, AttributeData->AttributeMap[ETDAttributeType::Damage]);
	}
	else
	{
		FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(SplineProgress, ESplineCoordinateSpace::World);
		FRotator NewRotation = Spline->GetRotationAtDistanceAlongSpline(SplineProgress, ESplineCoordinateSpace::World);
		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}

float ATDMonster::GetProgress() const
{
	return SplineProgress;
}

void ATDMonster::OnAttributeUpdateEvent(ETDAttributeType AttributeType)
{
	if(AttributeType == ETDAttributeType::Health)
	{
		if(AttributeData->AttributeMap[ETDAttributeType::Health] <= 0)
		{
			auto GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
			GameMode->GoldManager->ChangeGoldCount(GoldValue);
			GameMode->WaveManager->OnMonsterDestroyed(this);
			Destroy();
		}
		else
		{
			if(!IsValid(DamagedMaterial))
			{
				return;
			}
			MeshComponent->SetMaterial(0, DamagedMaterial);
			GetWorld()->GetTimerManager().ClearTimer(DamagedMaterialTimerHandle);
			GetWorld()->GetTimerManager().SetTimer(DamagedMaterialTimerHandle, this, &ATDMonster::ResetMaterial, DamagedMaterialDuration);
			
		}
	}
}

void ATDMonster::ResetMaterial()
{
	MeshComponent->SetMaterial(0, StartMaterial);
}



