#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TDAbilitySystem.generated.h"

class ATDTowerProjectile;
class UTDTowerAbility;


UENUM()
enum class ETDAttributeType : uint8
{
	Health,
	Damage,
	Speed
};

UENUM()
enum class ETDAbilitySpeed : uint8
{
	Instant,
	Lingering
};

UENUM()
enum class ETDAbilityCustomParameterTypes : uint8
{
	None,
	Grenade,
	Tesla
};

UENUM()
enum class ETDAbilitySortingType : uint8
{
	ClosestMonster,
	FurthestMonster,
	MostProgressOnPath,
	LeastProgressOnPath,
	NONE
};

USTRUCT(BlueprintType)
struct FTowerAbilityStats
{
	GENERATED_BODY()


	
	UPROPERTY(EditAnywhere)
	ETDAttributeType TargetAttribute;

	UPROPERTY(EditAnywhere)
	ETDAbilitySpeed AbilitySpeed;

	UPROPERTY(EditAnywhere)
	ETDAbilitySortingType SortingType;
	
	UPROPERTY(EditAnywhere)
	float AbilityMagnitude;
	
	UPROPERTY(EditAnywhere)
	float Cooldown;

	UPROPERTY(EditAnywhere)
	float Range;

	UPROPERTY(EditAnywhere)
	float ConeAngle;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="AbilitySpeed == EETDAbilitySpeed::Lingering", EditConditionHides))
	float Duration ;

	UPROPERTY(EditAnywhere,  meta=(EditCondition="AbilitySpeed == EETDAbilitySpeed::Lingering", EditConditionHides))
	bool IsAdditive;

	UPROPERTY(EditAnywhere)
	bool IsUsingProjectiles;
	 
	UPROPERTY(EditAnywhere, meta=(EditCondition="IsUsingProjectiles", EditConditionHides))
	float ProjectileSpeed;

	UPROPERTY(EditAnywhere, meta=(EditCondition="IsUsingProjectiles", EditConditionHides))
	TSubclassOf<ATDTowerProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere)
	int UpgradePrice;
	
	UPROPERTY(EditAnywhere)
	ETDAbilityCustomParameterTypes CustomParametersToShow;
	
	UPROPERTY(EditAnywhere, meta=(EditCondition="CustomParametersToShow == ETDAbilityCustomParameterTypes::Grenade", EditConditionHides))
	float RadiusOfBlast;

	UPROPERTY(EditAnywhere, meta=(EditCondition="CustomParametersToShow == ETDAbilityCustomParameterTypes::Tesla", EditConditionHides))
	int NumberOfRiples;
	
};




UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDAbilitySystem : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UTDAbilitySystem();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTDTowerAbility> AbilityClass;

	UPROPERTY()
	TObjectPtr<UTDTowerAbility> TowerAbility;

	UPROPERTY(EditAnywhere)
	TArray<FTowerAbilityStats> AbilityStatsOverride;

	UPROPERTY(VisibleAnywhere)
	int CurrentTowerLevel = 0;

public:
	UFUNCTION()
	void UpgradeTower();

	UFUNCTION()
	bool IsTowerAtMaxLevel(){return CurrentTowerLevel >= AbilityStatsOverride.Num() - 1;}

	UFUNCTION()
	void MarkAsDestroyed();

	UFUNCTION()
	int GetUpgradePrice(){return AbilityStatsOverride[CurrentTowerLevel].UpgradePrice;}
};
