#include "TeslaTurret.h"
#include "EnemyShip.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utils/TagStrings.h"

ATeslaTurret::ATeslaTurret() {
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
		}
		else if(Target != nullptr) {
			lightning->SetBeamTargetPoint(0, Target->GetActorLocation(), 0);
		}
	}

	if (Target == nullptr) {
		if (LastCheck > seconds) {
			LookForTarget();
		}
	}
	else {
		if(LastAttack > seconds){
			Attack();
		}
	}
}

void ATeslaTurret::Attack() {
	if (Target != nullptr) {

		lightning = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LightingParticle, GetActorLocation());
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
				LastAttack = seconds + AttackRate;
			}
		}
	}
	LastCheck = seconds + CheckRate;
}

TArray<FHitResult> ATeslaTurret::GetActorsInRange(float radius)
{
	TArray<FHitResult> HitResults;
	auto parent = GetOwner();
	FVector StartLocation = parent->GetActorLocation();
	FVector EndLocation = parent->GetActorLocation();
	EndLocation.Z += 0;

	ECollisionChannel ECC = ECollisionChannel::ECC_WorldStatic;
	FCollisionShape CollisionShape;
	CollisionShape.ShapeType = ECollisionShape::Sphere;
	CollisionShape.SetSphere(radius);
	GetWorld()->SweepMultiByChannel(HitResults, StartLocation, EndLocation, FQuat::FQuat(), ECC, CollisionShape);
	return HitResults;
}
