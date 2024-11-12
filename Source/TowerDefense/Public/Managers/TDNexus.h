#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDNexus.generated.h"

UCLASS()
class TOWERDEFENSE_API ATDNexus : public AActor
{
	GENERATED_BODY()

public:
	ATDNexus();

	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> MeshComponent;

	UPROPERTY(EditAnywhere)
	int StartNexusHealthPoints;
	
	UPROPERTY(VisibleAnywhere)
	int CurrentNexusHealthPoints;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnGameOver();
	
public :
	UFUNCTION()
	bool OnHit(int Damage);
};
