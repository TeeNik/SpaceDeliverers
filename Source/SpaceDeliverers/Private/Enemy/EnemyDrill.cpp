#include "EnemyDrill.h"
#include "Instrument.h"
#include "HealthComponent.h"
#include "Gun.h"

AEnemyDrill::AEnemyDrill() {
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AEnemyDrill::BeginPlay()
{
	HealthComponent->OnDeath.AddDynamic(this, &AEnemyDrill::OnDeath);
}

void AEnemyDrill::Interact(AInstrument *& inHand, ACharacter * character)
{
	if (inHand != NULL && inHand->GetType() == InstrumentType::Gun) {
		AGun* gun = Cast<AGun>(inHand);
		float damage = gun->GetDamage();
		HealthComponent->TakeDamage(damage);
	}
}

void AEnemyDrill::OnDeath(UHealthComponent* health)
{
	Destroy();
}
