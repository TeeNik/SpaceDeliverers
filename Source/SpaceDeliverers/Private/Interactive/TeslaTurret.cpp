#include "TeslaTurret.h"
#include "EnemyShip.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utils/TagStrings.h"
#include "HealthComponent.h"
#include "Components/BoxComponent.h"

ATeslaTurret::ATeslaTurret() {
	PrimaryActorTick.bCanEverTick = true;

	//RootPoint = CreateDefaultSubobject<USceneComponent>(TEXT("RootPoint"));
	//RootComponent = Box;

	//Mesh->SetRelativeLocation(FVector::ZeroVector);
	//Box->SetRelativeLocation(FVector::ZeroVector);

	SourcePoint = CreateDefaultSubobject<USceneComponent>(TEXT("SourcePoint"));
	SourcePoint->SetupAttachment(RootComponent);
	SmokeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeParticle"));
	SmokeParticle->SetupAttachment(RootComponent);
}

void ATeslaTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float seconds = GetWorld()->GetTimeSeconds();

	if (!IsValid(Target)) {
		if (seconds > LastCheck) {
			LookForTarget();
		}
	}
	else {
		if (seconds > LastAttack) {
			Attack();
		}
	}

	if (lightning != nullptr) {
		if (seconds >= LightningDestroyTime) {
			lightning->DestroyComponent();
			lightning = nullptr;
			if (IsValid(Target)) {
				Target->GetHealthComponent()->TakeDamage(Damage);
			}
		}
		else if(IsValid(Target)) {
			lightning->SetBeamTargetPoint(0, Target->GetActorLocation(), 0);
		}
	}
}

void ATeslaTurret::CrashReached()
{
	IDestructible::CrashReached();
	SmokeParticle->SetVisibility(true);
}

void ATeslaTurret::DestroyReached()
{
	Destroy();
}

void ATeslaTurret::Attack() {
	if (IsValid(Target)) {
		lightning = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LightingParticle, SourcePoint->GetComponentLocation());
		lightning->SetBeamTargetPoint(0, Target->GetActorLocation(), 0);
		lightning->SetWorldScale3D(FVector(2, 2, 2));
		LightningDestroyTime = GetWorld()->GetTimeSeconds() + LightningDuration;
		LastAttack = GetWorld()->GetTimeSeconds() + AttackRate;
	}
}

void ATeslaTurret::LookForTarget()
{
	float seconds = GetWorld()->GetTimeSeconds();
	TArray<FHitResult> hits = GetActorsInRange(AttackRadius);
	for (auto It = hits.CreateIterator(); It; It++)
	{
		auto actor = It->Actor;
		if (actor->ActorHasTag(TagStrings::EnemyShipTag)) {
			AEnemyShip* ship = Cast<AEnemyShip>(It->GetActor());
			if (IsValid(ship)) {
				Target = ship;
				ship->OnDeathCallback.AddDynamic(this, &ATeslaTurret::OnTargetDestroy);
				LastAttack = seconds + AttackRate;
				break;
			}
		}
	}
	LastCheck = seconds + CheckRate;
}

TArray<FHitResult> ATeslaTurret::GetActorsInRange(float radius)
{
	TArray<FHitResult> HitResults;
	FVector location = GetActorLocation();

	ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(radius);
	GetWorld()->SweepMultiByChannel(HitResults, location, location, FQuat::FQuat(), ECC, CollisionShape);
	return HitResults;
}

void ATeslaTurret::OnTargetDestroy(AEnemyShip* ship)
{
	Target = nullptr;
	float seconds = GetWorld()->GetTimeSeconds();
	LastCheck = seconds + CheckRate;
	LastAttack = seconds + AttackRate;
}
