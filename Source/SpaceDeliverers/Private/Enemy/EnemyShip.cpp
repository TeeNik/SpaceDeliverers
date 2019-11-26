#include "EnemyShip.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "WeaponProjectile.h"
#include "HealthComponent.h"

AEnemyShip::AEnemyShip()
{
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	HealthComponent->OnTakeDamage.AddDynamic(this, &AEnemyShip::OnTakeDamage);
	HealthComponent->OnDeath.AddDynamic(this, &AEnemyShip::OnDeath);
}

void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AEnemyShip::ShootByTimer, FireRate, true);
}

void AEnemyShip::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	FVector newLocation = GetActorLocation();
	float deltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
	newLocation.X += deltaHeight * XValue;
	newLocation.Y += deltaHeight * YValue;
	newLocation.Z += deltaHeight * ZValue;
	RunningTime += DeltaTime;
	SetActorLocation(newLocation);
}

void AEnemyShip::ShootByTimer()
{
	if (ProjectileBase != NULL && FireRate != 0)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle_1"));
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			World->SpawnActor<AActor>(ProjectileBase, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}

void AEnemyShip::OnTakeDamage(int health)
{
	GLog->Log("AEnemyShip::OnTakeDamage");
}

void AEnemyShip::OnDeath()
{
	GLog->Log("Death");
	Destroy();
}
