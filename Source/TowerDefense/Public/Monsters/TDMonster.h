#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDMonster.generated.h"

enum class ETDAttributeType : uint8;
class UTDAttributeData;
class USplineComponent;

UCLASS()
class TOWERDEFENSE_API ATDMonster : public AActor
{
	GENERATED_BODY()

public:
	ATDMonster();

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UTDAttributeData> AttributeData;
	
protected:
	UPROPERTY()
	float SplineProgress;
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> DamagedMaterial;

	UPROPERTY(EditAnywhere)
	float DamagedMaterialDuration;

	FTimerHandle DamagedMaterialTimerHandle;
	
	UPROPERTY(EditAnywhere)
	int GoldValue = 50;

	UPROPERTY()
	TObjectPtr<UMaterialInterface> StartMaterial;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void ResetMaterial();
	
public:
	UFUNCTION()
	virtual void OnSplineMovement(USplineComponent* Spline, float DeltaTime);

	UFUNCTION()
	float GetProgress() const;

	UFUNCTION()
	void OnAttributeUpdateEvent(ETDAttributeType AttributeType);
};
