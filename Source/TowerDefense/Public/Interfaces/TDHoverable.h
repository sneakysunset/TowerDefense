#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDHoverable.generated.h"

UINTERFACE()
class UTDHoverable : public UInterface
{
	GENERATED_BODY()
};


class TOWERDEFENSE_API ITDHoverable
{
	GENERATED_BODY()

public:
	virtual void OnStartHover() = 0;
	virtual void OnStopHover() = 0;
};
