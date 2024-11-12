#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDSelectable.generated.h"

UINTERFACE()
class UTDSelectable : public UInterface
{
	GENERATED_BODY()
};


class TOWERDEFENSE_API ITDSelectable
{
	GENERATED_BODY()

public:
	virtual void OnSelect() = 0;
	virtual void OnUnselect() = 0;
};
