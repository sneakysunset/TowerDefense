#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/TDClickable.h"
#include "Interfaces/TDHoverable.h"
#include "Managers/TDGameMode.h"
#include "TDTowerSlot.generated.h"

class ATDGameMode;
class ATDTower_Base;


UCLASS()
class TOWERDEFENSE_API ATDTowerSlot : public AActor, public ITDHoverable, public ITDClickable
{
	GENERATED_BODY()

public:
	ATDTowerSlot();
	
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> HighlightedMaterial;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterialInterface> HighlightNotEnoughGoldMaterial;
	
	UPROPERTY()
	TObjectPtr<UMaterialInterface> NormalMaterial;
	
	UPROPERTY()
	TObjectPtr<ATDTower_Base> CurrentTower;

	TObjectPtr<ATDGameMode> CurrentGameMode;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnStartHover() override;
	virtual void OnStopHover() override;
	virtual void OnClick() override;
	
public:
	UFUNCTION()
	ATDTower_Base* GetTower(){return CurrentTower;}

	UFUNCTION()
	void SetTower(ATDTower_Base* NewTower){CurrentTower = NewTower;}

	UFUNCTION()
	void OnTowerDestroyed(){CurrentTower = nullptr;}
};
