#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDGoldManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDGoldManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDGoldManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
