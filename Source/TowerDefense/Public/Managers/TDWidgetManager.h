#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDWidgetManager.generated.h"

class UTDMainUserWidget;

UENUM(BlueprintType, Blueprintable)
enum class ETDEditMode : uint8
{
	ROTATE = 0,
	DELETE_TOWER = 1,
	UPGRADE = 2
};

UENUM(BlueprintType, Blueprintable)
enum class ETDTowerType : uint8
{
	SubmachineGun = 0,
	Frost = 1,
	Grenade = 2,
	Tesla = 3
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDWidgetManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDWidgetManager();

	UPROPERTY(EditAnywhere)
	TSubclassOf<UTDMainUserWidget> WidgetClass;

	UPROPERTY()
	TObjectPtr<UTDMainUserWidget> MainUserWidget;

	UPROPERTY(VisibleAnywhere)
	ETDTowerType CurrentTowerSpawnType = ETDTowerType::SubmachineGun;

	UPROPERTY(VisibleAnywhere)
	ETDEditMode CurrentEditMode = ETDEditMode::ROTATE;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	ETDEditMode GetEditMode(){return CurrentEditMode;}
	
	UFUNCTION(BlueprintCallable)
	void SetEditMode(ETDEditMode NewEditMode){CurrentEditMode = NewEditMode;}

	UFUNCTION(BlueprintCallable)
	ETDTowerType GetCurrentTowerSpawnType(){return CurrentTowerSpawnType;}
	
	UFUNCTION(BlueprintCallable)
	void SetTowerType(ETDTowerType NewTowerType){CurrentTowerSpawnType = NewTowerType;}

	UFUNCTION()
	void UpdateWidgetUpgradePrice(int NewUpgradePrice);

	UFUNCTION()
	void UpdateWidgetNexusHP(float newPercent);
};
