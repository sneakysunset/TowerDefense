#pragma once

#include "CoreMinimal.h"
#include "TDAbilitySystem.h"
#include "UObject/Object.h"
#include "TDTowerAbility.generated.h"

class ATDGameMode;
class ATDMonster_Base;
enum class ETDAttributeType : uint8;



UCLASS(Abstract)
class TOWERDEFENSE_API UTDTowerAbility : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	FTowerAbilityStats AbilityStats;

	UPROPERTY()
	TObjectPtr<AActor> Owner;

	UPROPERTY()
	TObjectPtr<ATDGameMode> GameMode;
	
	FTimerHandle ActivationTimerHandle;

	UPROPERTY()
	bool IsMonsterInRange;

	UFUNCTION()
	virtual void Initialize(AActor* Outer, FTowerAbilityStats StatsOverride);
	
	UFUNCTION()
	virtual void ActivateAbility();

	UFUNCTION()
	virtual void AbilityEffect();

	UFUNCTION()
	virtual void StopAbility();

	UFUNCTION()
	virtual void PauseAbility(bool ToPause);
	
	UFUNCTION()
	bool GetMonstersInCone(TArray<ATDMonster_Base*> OutMonsters) const;

	UFUNCTION()
	void DrawDebugCone();
};
