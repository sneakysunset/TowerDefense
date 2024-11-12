#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDWaveManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDWaveManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDWaveManager();

protected:
	virtual void BeginPlay() override;
};
