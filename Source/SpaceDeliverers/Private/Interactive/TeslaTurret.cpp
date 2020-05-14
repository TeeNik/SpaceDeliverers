#include "TeslaTurret.h"
#include "EnemyShip.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utils/TagStrings.h"
#include "HealthComponent.h"

ATeslaTurret::ATeslaTurret() {
	PrimaryActorTick.bCanEverTick = true;
	SourcePoint = CreateDefaultSubobject<USceneComponent>(TEXT("SourcePoint"));
	SourcePoint->SetupAttachment(RootComponent);
}

void ATeslaTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float seconds = GetWorld()->GetTimeSeconds();

	if (lightning != nullptr) {
		if (seconds >= LightingDestroyTime) {
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

	if (!IsValid(Target)) {
		if (seconds > LastCheck) {
			LookForTarget();
		}
	}
	else {
		if(seconds > LastAttack){
			Attack();
		}
	}
}

void ATeslaTurret::Attack() {
	if (IsValid(Target)) {
		lightning = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LightingParticle, SourcePoint->GetComponentLocation());
		lightning->SetBeamTargetPoint(0, Target->GetActorLocation(), 0);
		LightingDestroyTime = GetWorld()->GetTimeSeconds() + LightingDuration;
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
				ship->GetHealthComponent()->OnDeath.AddDynamic(this, &ATeslaTurret::OnTargetDestroy);
				LastAttack = seconds + AttackRate;
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

void ATeslaTurret::OnTargetDestroy()
{
	Target == nullptr;
	float seconds = GetWorld()->GetTimeSeconds();
	LastCheck = seconds + CheckRate;
	LastAttack = seconds + AttackRate;
}
