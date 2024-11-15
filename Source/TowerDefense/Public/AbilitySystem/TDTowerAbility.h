#pragma once

#include "CoreMinimal.h"
#include "TDAbilitySystem.h"
#include "UObject/Object.h"
#include "TDTowerAbility.generated.h"

class ATDGameMode;
class ATDMonster;
enum class ETDAttributeType : uint8;



UCLASS(Abstract)
class TOWERDEFENSE_API UTDTowerAbility : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	FTowerAbilityStats AbilityStats;

	UPROPERTY()
	TObjectPtr<AActor> Owner;

	UPROPERTY()
	TObjectPtr<ATDGameMode> GameMode;
	
	UPROPERTY()
	bool IsMarkedAsDeleted;
	
	FTimerHandle ActivationTimerHandle;


public:
	UFUNCTION()
	virtual void Initialize(AActor* Outer, FTowerAbilityStats StatsOverride);
	
	UFUNCTION()
	virtual void ActivateAbility();

	UFUNCTION()
	virtual void OnAbilityTriggered();

	UFUNCTION()
	virtual void OnProjectileHit(AActor* HitActor);
	
	UFUNCTION()
	virtual void AbilityEffect(AActor* HitActor = nullptr);

	UFUNCTION()
	bool GetMonstersInCone(TArray<ATDMonster*>& OutMonsters) const;

	UFUNCTION()
	void UpdateStats(FTowerAbilityStats StatsOverride);
	
	UFUNCTION()
	void DrawDebugCone();

	UFUNCTION()
	void SetMarkedAsDeleted(){IsMarkedAsDeleted = true;}
};
