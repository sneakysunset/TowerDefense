#pragma once

#include "CoreMinimal.h"
#include "TDAbilitySystem.h"
#include "Components/ActorComponent.h"
#include "TDAttributeData.generated.h"

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnAttributeUpdate, ETDAttributeType, Type);

enum class ETDAbilitySpeed : uint8;
enum class ETDAttributeType : uint8;

USTRUCT()
struct FLingeringEffectData
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	ETDAttributeType Type;
	
	UPROPERTY(VisibleAnywhere)
	float Value;

	UPROPERTY(VisibleAnywhere)
	bool IsAdditive;
	
	FTimerHandle TimerHandle;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOWERDEFENSE_API UTDAttributeData : public UActorComponent
{
	GENERATED_BODY()

public:
	UTDAttributeData();

	FOnAttributeUpdate OnAttributeUpdateDelegate;
	
	UPROPERTY(EditAnywhere)
	TMap<ETDAttributeType, float> AttributeMap;
protected:

	UPROPERTY()
	TMap<ETDAttributeType, float> BaseAttributeMap;

	UPROPERTY(VisibleAnywhere)
	TMap<int, FLingeringEffectData> LingeringEffectsDatas;

	UPROPERTY()
	int LastID;
	
protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void ApplyAttributeChange(float Value, ETDAttributeType AttributeType, ETDAbilitySpeed AbilityType = ETDAbilitySpeed::Instant, float Duration = 0, bool IsAdditive = true);

	UFUNCTION()
	void DisableAttribute(int ID);
};
