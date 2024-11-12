#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDMonster_Base.generated.h"

class USplineComponent;

UCLASS()
class TOWERDEFENSE_API ATDMonster_Base : public AActor
{
	GENERATED_BODY()

public:
	ATDMonster_Base();

protected:
	UPROPERTY(EditAnywhere)
	float Speed;

	UPROPERTY(EditAnywhere)
	int Damage;
	
	UPROPERTY()
	float SplineProgress;
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> MeshComponent;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	virtual void OnSplineMovement(USplineComponent* Spline, float DeltaTime);
};
