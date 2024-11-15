#include "AbilitySystem/TDAttributeData.h"

#include "AbilitySystem/TDAbilitySystem.h"

UTDAttributeData::UTDAttributeData()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTDAttributeData::BeginPlay()
{
	Super::BeginPlay();
	BaseAttributeMap = AttributeMap;
}

void UTDAttributeData::ApplyAttributeChange(float Value, ETDAttributeType AttributeType, ETDAbilitySpeed AbilityType, float Duration, bool IsAdditive)
{
	if(AbilityType == ETDAbilitySpeed::Lingering)
	{
		float PotentialValue = IsAdditive ? BaseAttributeMap[AttributeType] - Value : BaseAttributeMap[AttributeType] * Value;
		if(PotentialValue < AttributeMap[AttributeType])
		{
			AttributeMap[AttributeType] = PotentialValue;
		}
		
		FLingeringEffectData NewData;
		NewData.Type = AttributeType;
		NewData.Value = Value;
		NewData.IsAdditive = IsAdditive;
		LastID++;
		LingeringEffectsDatas.Add(LastID, NewData);

		FTimerDelegate TimerDelegate;
		TimerDelegate.BindUFunction(this, FName("DisableAttribute"), LastID);
		
		GetWorld()->GetTimerManager().SetTimer(NewData.TimerHandle, TimerDelegate, Duration, false);
	}
	else
	{
		AttributeMap[AttributeType] -= Value;
	}

	OnAttributeUpdateDelegate.ExecuteIfBound(AttributeType);
}

void UTDAttributeData::DisableAttribute(int ID)
{
	ETDAttributeType Type = LingeringEffectsDatas[ID].Type;
	float LowestPotential = BaseAttributeMap[Type];
	LingeringEffectsDatas.Remove(ID);
	for(const auto& Data : LingeringEffectsDatas)
	{
		float Potential = Data.Value.IsAdditive ? BaseAttributeMap[Type] -  Data.Value.Value : BaseAttributeMap[Type] *  Data.Value.Value;
		if(Potential < LowestPotential)
		{
			LowestPotential = Potential;
		}
	}
	AttributeMap[Type] = LowestPotential;
	//OnAttributeUpdateDelegate.ExecuteIfBound(Type);
}

