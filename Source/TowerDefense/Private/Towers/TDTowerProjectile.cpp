#include "Towers/TDTowerProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


ATDTowerProjectile::ATDTowerProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = ProjectileMesh;
}

void ATDTowerProjectile::Initialize(float InSpeed, AActor* InTargetActor)
{
	GetWorld()->GetTimerManager().SetTimer(LifeTimeTimerHandle, this, &ATDTowerProjectile::OnLifeTimeEnded, LifeTime, false);
	ProjectileMesh->OnComponentHit.AddDynamic(this, &ATDTowerProjectile::OnHit);
	Speed = InSpeed;
}

void ATDTowerProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void ATDTowerProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SetActorLocation(GetActorLocation() + GetActorForwardVector() * Speed * DeltaTime, true);
}

void ATDTowerProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	OnProjectileHitEvent.ExecuteIfBound(OtherActor);
	Destroy();
}

void ATDTowerProjectile::OnLifeTimeEnded()
{
	Destroy();
}

