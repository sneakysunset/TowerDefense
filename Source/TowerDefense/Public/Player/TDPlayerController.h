#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TDPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class ITDHoverable;

UCLASS()
class TOWERDEFENSE_API ATDPlayerController : public APlayerController
{
	GENERATED_BODY()

	ATDPlayerController();
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Default Mapping Context"))
	UInputMappingContext* IMC_Default;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "PlayerPawn|Input", meta=(DisplayName = "Left Click Press Action"))
	UInputAction* IA_LeftClickOnTower;

	TScriptInterface<ITDHoverable> CurrentHoveredElement;


private:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupInputComponent() override;
	void OnLeftClickOnTowerSlot();
};

