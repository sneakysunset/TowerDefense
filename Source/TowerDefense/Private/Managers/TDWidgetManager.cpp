#include "Managers/TDWidgetManager.h"
#include "Widgets/TDMainUserWidget.h"

UTDWidgetManager::UTDWidgetManager()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTDWidgetManager::BeginPlay()
{
	Super::BeginPlay();
	if(WidgetClass)
	{
		MainUserWidget = Cast<UTDMainUserWidget>(CreateWidget(GetWorld(), WidgetClass));
		if(MainUserWidget)
		{
			MainUserWidget->AddToViewport();
		}
	}
}

void UTDWidgetManager::UpdateWidgetUpgradePrice(int NewUpgradePrice)
{
	MainUserWidget->UpdateUpgradePrice(NewUpgradePrice);
}

void UTDWidgetManager::UpdateWidgetNexusHP(float newPercent)
{
	MainUserWidget->OnNexusHealthChange(newPercent);
}

