#include "Shield.h"
#include "ShieldGenerator.h"
#include "System/SpaceLevelScript.h"
#include "HealthComponent.h"

AShield::AShield()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
}

void AShield::BeginPlay()
{
	Super::BeginPlay();

	auto level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	if (IsValid(level)) {
		Generators = level->GetGenerators();

		for (auto generator : Generators)
		{
			generator->OnEnergyUpdate.AddDynamic(this, &AShield::OnShieldUpdate);
		}
	}

	HealthComponent->OnTakeDamage.AddDynamic(this, &AShield::OnTakeDamage);
}

void AShield::OnShieldUpdate()
{

}

void AShield::OnTakeDamage_Implementation(int health)
{

}
