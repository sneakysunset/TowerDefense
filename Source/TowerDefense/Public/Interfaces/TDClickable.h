#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TDClickable.generated.h"

UINTERFACE()
class UTDClickable : public UInterface
{
	GENERATED_BODY()
};


class TOWERDEFENSE_API ITDClickable
{
	GENERATED_BODY()

public:
	virtual void OnClick() = 0;
};
