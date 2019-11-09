#include "WeaponProjectile.h"
#include "Components/BoxComponent.h"
#include "Components/HealthComponent.h"
#include "Components/StaticMeshComponent.h"

AWeaponProjectile::AWeaponProjectile()
{
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = BoxCollider;
	Mesh->SetupAttachment(RootComponent);

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &AWeaponProjectile::OnOverlapBegin);
}

void AWeaponProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponProjectile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if (OtherActor->ActorHasTag(TargetTag)) {
		auto health = Cast<UHealthComponent>(OtherActor->GetComponentByClass(UHealthComponent::StaticClass()));
		if (IsValid(health)) {
			health->TakeDamage(Damage);
		}
	}

}
