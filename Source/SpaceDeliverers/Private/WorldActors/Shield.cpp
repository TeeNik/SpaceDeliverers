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
}

void AShield::Initialize()
{
	auto level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	if (IsValid(level)) {
		Generators = &level->GetGenerators();
		for (auto generator : *Generators)
		{
			generator->OnEnergyUpdate.AddDynamic(this, &AShield::OnGeneratorEnergyUpdate);
			CurrentEnergy += generator->GetMaxValue();
		}
		MaxEnergy = CurrentEnergy;
	}
	BroadcastShieldPercent();
	HealthComponent->OnTakeDamage.AddDynamic(this, &AShield::OnTakeDamage);
}

void AShield::OnGeneratorEnergyUpdate()
{
	CurrentEnergy = 0;
	for (auto generator : *Generators) {
		CurrentEnergy += generator->GetCurrentValue();
	}
	BroadcastShieldPercent();
}

void AShield::BroadcastShieldPercent()
{
	float percent = CurrentEnergy / MaxEnergy;
	UE_LOG(LogTemp, Log, TEXT("percent: %g"), percent);
	OnShieldUpdate.Broadcast(percent);
}

void AShield::OnTakeDamage(int health, UHealthComponent* hc)
{
	OnTakeDamageBP(health);
	for (int i = 0; i < Generators->Num(); ++i) {
		auto generator = (*Generators)[i];
		if (generator->GetCurrentValue() > 0) {
			generator->ReduceEnergy();
			--CurrentEnergy;
			BroadcastShieldPercent();
			return;
		}
	}
}

void AShield::OnTakeDamageBP_Implementation(int health)
{
}
