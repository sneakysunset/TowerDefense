#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDAbilitySystem.generated.h"

class UTDTowerAbility;


UENUM()
enum class ETDAttributeType : uint8
{
	Health,
	Damage,
	Speed
};

USTRUCT(BlueprintType)
struct FTowerAbilityStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETDAttributeType AbilityType;

	UPROPERTY()
	float AbilityMagnitude;
	
	UPROPERTY(EditAnywhere)
	float Cooldown = 1.0f;

	UPROPERTY(EditAnywhere)
	float Range = 500.0f;

	UPROPERTY(EditAnywhere)
	float ConeAngle = 45.0f;

	UPROPERTY(EditAnywhere)
	bool IsActivatingWithNoMonsterInRange;
	
	UPROPERTY(EditAnywhere)
	float InactiveCheckForMonstersRate = .25f;
};




UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDAbilitySystem : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UTDAbilitySystem();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTDTowerAbility> AbilityClass;

	UPROPERTY()
	TObjectPtr<UTDTowerAbility> TowerAbility;

	UPROPERTY(EditAnywhere)
	FTowerAbilityStats AbilityStatsOverride;
};
