#include "Monsters/TDMonster_Base.h"
#include "Components/SplineComponent.h"
#include "Managers/TDGameMode.h"

ATDMonster_Base::ATDMonster_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = MeshComponent;
}

void ATDMonster_Base::BeginPlay()
{
	Super::BeginPlay();
}

void ATDMonster_Base::OnSplineMovement(USplineComponent* Spline, float DeltaTime)
{
	float MovementDelta = Speed * DeltaTime;
	SplineProgress += MovementDelta;
	if(SplineProgress >= Spline->GetSplineLength())
	{
		Cast<ATDGameMode>(GetWorld()->GetAuthGameMode())->OnHitNexus(this, Damage);
	}
	else
	{
		FVector NewLocation = Spline->GetLocationAtDistanceAlongSpline(SplineProgress, ESplineCoordinateSpace::World);
		FRotator NewRotation = Spline->GetRotationAtDistanceAlongSpline(SplineProgress, ESplineCoordinateSpace::World);
		SetActorLocationAndRotation(NewLocation, NewRotation);
	}
}


