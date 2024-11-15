#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDTowerProjectile.generated.h"

class UBoxComponent;
class ATDMonster;
class UProjectileMovementComponent;
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnProjectileHit, AActor*, HitActor);

UCLASS()
class TOWERDEFENSE_API ATDTowerProjectile : public AActor
{
	GENERATED_BODY()

public:
	ATDTowerProjectile();

	UFUNCTION()
	virtual void Initialize(float InSpeed, AActor* InTargetActor);

	FOnProjectileHit OnProjectileHitEvent;

	
protected:
	UPROPERTY(EditAnywhere, Category="", meta=(AllowPrivateAccess))
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditAnywhere)
	float LifeTime;

	UPROPERTY()
	float Speed;
	
	FTimerHandle LifeTimeTimerHandle;
	
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnLifeTimeEnded();
};
