#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDGoldManager.generated.h"


class ATDGameMode;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDGoldManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDGoldManager();

private:
	UPROPERTY(EditAnywhere)
	int StartGoldCount;
	
	UPROPERTY(VisibleAnywhere)
	int CurrentGoldCount;

	UPROPERTY()
	TObjectPtr<ATDGameMode> OwningGameMode;
	
public:
	UFUNCTION()
	void OnStart();
	
	UFUNCTION()
	bool CanPurchaseTower();

	UFUNCTION()
	bool CanPurchaseUpgrade(int UpgradeCost);

	UFUNCTION()
	void PurchaseTower();

	UFUNCTION()
	void ChangeGoldCount(int Cost);

	UFUNCTION(BlueprintCallable)
	int GetGoldAmount(){return CurrentGoldCount;}

};
