#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDPlayerPawn.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	ATDPlayerPawn();
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
