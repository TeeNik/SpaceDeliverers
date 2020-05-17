#include "EnemyShip.h"
#include "TimerManager.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "WeaponProjectile.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "Utils/TagStrings.h"

AEnemyShip::AEnemyShip()
{
	PrimaryActorTick.bCanEverTick = true;
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Box);
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	Tags.Add(TagStrings::EnemyShipTag);
}

void AEnemyShip::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddDynamic(this, &AEnemyShip::OnDeath);
}

void AEnemyShip::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	if (IsMovementAble) {
		FVector newLocation = GetActorLocation();
		float deltaHeight = FMath::Sin(RunningTime + DeltaTime) - FMath::Sin(RunningTime);
		newLocation.X += deltaHeight * XValue;
		newLocation.Y += deltaHeight * YValue;
		newLocation.Z += deltaHeight * ZValue;
		RunningTime += DeltaTime;
		SetActorLocation(newLocation);
	}
}

void AEnemyShip::Shoot()
{
	if (ProjectileBase != NULL && IsMovementAble)
	{
		const FRotator SpawnRotation = GetActorRotation();
		const FVector SpawnLocation = Mesh->GetSocketLocation(TEXT("Muzzle_1"));
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		GetWorld()->SpawnActor<AActor>(ProjectileBase, SpawnLocation, SpawnRotation, ActorSpawnParams);
	}
}

void AEnemyShip::OnDeath()
{
	if (ExplosionParticle != NULL) {
		auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation());
		particle->SetWorldScale3D(ParticleSize);
	}
	OnDeathCallback.Broadcast(this);
	Destroy();
}

void AEnemyShip::StartMovement()
{
	IsMovementAble = true;
}
