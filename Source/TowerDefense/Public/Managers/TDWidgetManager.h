#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDWidgetManager.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDWidgetManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDWidgetManager();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
