#include "EnemyShip.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"

AEnemyShip::AEnemyShip()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;
}

void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyShip::ShootByTimer, FireRate, true);
}

void AEnemyShip::ShootByTimer()
{
	GLog->Log("Enemy Fire");
}
