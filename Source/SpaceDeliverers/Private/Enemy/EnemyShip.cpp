#include "EnemyShip.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "WeaponProjectile.h"
#include "HealthComponent.h"

AEnemyShip::AEnemyShip()
{
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyShip::ShootByTimer, FireRate, true);
}

void AEnemyShip::ShootByTimer()
{
	GLog->Log("Enemy Fire");

	if (ProjectileBase != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			/*const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle_1"));
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			World->SpawnActor<AActor>(ProjectileBase, SpawnLocation, SpawnRotation, ActorSpawnParams);*/
		}
	}
}
