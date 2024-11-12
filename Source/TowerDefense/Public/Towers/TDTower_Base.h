#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TDClickable.h"
#include "Interfaces/TDHoverable.h"
#include "TDTower_Base.generated.h"

DECLARE_DYNAMIC_DELEGATE(FOnDestruction);

class ATDGameMode;

UCLASS()
class TOWERDEFENSE_API ATDTower_Base : public AActor, public ITDHoverable, public ITDClickable
{
	GENERATED_BODY()

public:
	ATDTower_Base();

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> HighlightedMaterial;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> HighlightNotEnoughGoldMaterial;
	
	UPROPERTY()
	TObjectPtr<UMaterialInterface> NormalMaterial;

	UPROPERTY()
	TObjectPtr<ATDGameMode> CurrentGameMode;

	UPROPERTY(EditAnywhere)
	int UpgradeCost;

public:
	FOnDestruction OnDestructionEvent;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void OnStartHover() override;
	virtual void OnStopHover() override;
	virtual void OnClick() override;
	virtual void Destroyed() override;;

	UFUNCTION()
	virtual void UpgradeTower();
};
