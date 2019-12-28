#include "EnemyDrill.h"
#include "Instrument.h"
#include "HealthComponent.h"
#include "Gun.h"
#include "InteractionComponent.h"

AEnemyDrill::AEnemyDrill() {
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyDrill::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddDynamic(this, &AEnemyDrill::OnDeath);
}

void AEnemyDrill::Interact(UInteractionComponent* interComp, ACharacter * character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Gun) {
		const AGun* gun = Cast<AGun>(inHand);
		float damage = gun->GetDamage();
		gun->Shoot(this);
		HealthComponent->TakeDamage(damage);
	}
}

void AEnemyDrill::OnDeath(UHealthComponent* health)
{
	Destroy();
}
