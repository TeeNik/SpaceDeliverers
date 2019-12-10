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
	GLog->Log(TEXT("BeginPlay"));
	UE_LOG(LogTemp, Log, TEXT("BeginPlay"));

	auto level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	if (IsValid(level)) {
		Generators = &level->GetGenerators();
		UE_LOG(LogTemp, Log, TEXT("Generators: %d"), Generators->Num());
		for (auto generator : *Generators)
		{
			generator->OnEnergyUpdate.AddDynamic(this, &AShield::OnGeneratorEnergyUpdate);
			CurrentEnergy += generator->GetMaxValue();
			UE_LOG(LogTemp, Log, TEXT("CurrenGetMaxValuetEnergy: %d"), generator->GetMaxValue());
			UE_LOG(LogTemp, Log, TEXT("CurrentEnergy: %d"), CurrentEnergy);

		}
	}
	UE_LOG(LogTemp, Log, TEXT("CurrentEnergy: %d"), CurrentEnergy);
	HealthComponent->OnTakeDamage.AddDynamic(this, &AShield::OnTakeDamage);
}

void AShield::OnGeneratorEnergyUpdate()
{
	CurrentEnergy = 0;
	for (auto generator : *Generators) {
		CurrentEnergy += generator->GetCurrentValue();
		UE_LOG(LogTemp, Log, TEXT("generator->GetCurrentValue(): %d"), generator->GetCurrentValue());
	}
	BroadcastShieldPercent();
	UE_LOG(LogTemp, Log, TEXT("Energy: %d"), CurrentEnergy);
}

void AShield::BroadcastShieldPercent()
{
	float percent = CurrentEnergy / MaxEnergy;
	OnShieldUpdate.Broadcast(percent);
}

void AShield::OnTakeDamage(int health)
{
	OnTakeDamageBP(health);
	UE_LOG(LogTemp, Log, TEXT("OnTakeDamage_Implementation"));
	for (int i = 0; i < Generators->Num(); ++i) {
		auto generator = (*Generators)[i];
		if (generator->GetCurrentValue() > 0) {
			generator->ReduceEnergy();
			--CurrentEnergy;
			BroadcastShieldPercent();
			UE_LOG(LogTemp, Log, TEXT("Energy: %d"), CurrentEnergy);
			return;
		}
	}
}

void AShield::OnTakeDamageBP_Implementation(int health)
{
}
