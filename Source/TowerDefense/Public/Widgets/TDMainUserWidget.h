#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TDMainUserWidget.generated.h"

UCLASS()
class TOWERDEFENSE_API UTDMainUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void UpdateCost(int NewCost);

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateUpgradePrice(int newUpgradePrice);

};
