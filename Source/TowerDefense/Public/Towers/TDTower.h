#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TDClickable.h"
#include "Interfaces/TDHoverable.h"
#include "TDTower.generated.h"

class UTDTowerAbility;
class UTDAbilitySystem;
DECLARE_DYNAMIC_DELEGATE(FOnDestruction);

class ATDGameMode;

UCLASS()
class TOWERDEFENSE_API ATDTower : public AActor, public ITDHoverable, public ITDClickable
{
	GENERATED_BODY()

public:
	ATDTower();

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UTDAbilitySystem> AbilitySystem;
	
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

public:
	FOnDestruction OnDestructionEvent;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnStartHover() override;
	virtual void OnStopHover() override;
	virtual void OnClick() override;
	virtual void Destroyed() override;;
};
