#include "TowerDefense/Public/Managers/TDMonsterSpline.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"


ATDMonsterSpline::ATDMonsterSpline()
{
	PrimaryActorTick.bCanEverTick = true;
	SplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
}

void ATDMonsterSpline::BeginPlay()
{
	Super::BeginPlay();
}


void ATDMonsterSpline::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(OnSplineMovementDelegate.IsBound())
	{
		OnSplineMovementDelegate.Broadcast(SplineComponent, DeltaTime);
	}
}

void ATDMonsterSpline::UpdateMesh()
{
	if(!IsValid(SplineMesh) || !IsValid(SplineMaterial))
	{
		return;
	}

	for (USplineMeshComponent* SplineMeshComponent : SplineMeshComponents)
	{
		if (SplineMeshComponent)
		{
			SplineMeshComponent->DestroyComponent();
		}
	}
	SplineMeshComponents.Empty();
	
	const auto BoundingBox = SplineMesh->GetBoundingBox();
	const auto Dimensions = BoundingBox.Min.GetAbs() +  BoundingBox.Max.GetAbs();
	const float XLength = Dimensions.X;

	const int NumOfSpline = FMath::FloorToInt(SplineComponent->GetSplineLength() / XLength);
	SplineMeshComponents.Reserve(NumOfSpline);
	
	for(int i = 0; i < NumOfSpline; i++)
	{
		const FVector StartPositionAlongSpline = SplineComponent->GetLocationAtDistanceAlongSpline
			(i * XLength, ESplineCoordinateSpace::Local);
		const FVector StartTangentAlongSpline = SplineComponent->GetTangentAtDistanceAlongSpline
			(i * XLength, ESplineCoordinateSpace::Local).GetClampedToSize(0, XLength);
		const FVector EndPositionAlongSpline = SplineComponent->GetLocationAtDistanceAlongSpline
			((i + 1) * XLength, ESplineCoordinateSpace::Local);
		const FVector EndTangentAlongSpline = SplineComponent->GetTangentAtDistanceAlongSpline
			((i + 1) * XLength, ESplineCoordinateSpace::Local).GetClampedToSize(0, XLength);
		
		SplineMeshComponents.Add(NewObject<USplineMeshComponent>(this, NAME_None, RF_Transactional));
		SplineMeshComponents[i]->SetForwardAxis(ESplineMeshAxis::X, true);
		SplineMeshComponents[i]->SetStaticMesh(SplineMesh);
		SplineMeshComponents[i]->SetStartAndEnd(StartPositionAlongSpline, StartTangentAlongSpline,
			EndPositionAlongSpline, EndTangentAlongSpline, true);
		SplineMeshComponents[i]->RegisterComponent();
		SplineMeshComponents[i]->SetMaterial(0, SplineMaterial);
	}
}

