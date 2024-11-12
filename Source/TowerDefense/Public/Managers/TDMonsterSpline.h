#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDMonsterSpline.generated.h"

class USplineMeshComponent;
class USplineComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpineMovement, USplineComponent*, Spline, float, DeltaTime);


UCLASS()
class TOWERDEFENSE_API ATDMonsterSpline : public AActor
{
	GENERATED_BODY()

public:
	ATDMonsterSpline();

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<USplineComponent> SplineComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMesh> SplineMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> SplineMaterial; 
	
	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<USplineMeshComponent>> SplineMeshComponents;
	
	FOnSpineMovement OnSplineMovementDelegate;
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(CallInEditor)
	void UpdateMesh();
};
