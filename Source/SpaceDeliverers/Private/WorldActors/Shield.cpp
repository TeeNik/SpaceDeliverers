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
		Generators = level->GetGenerators();
		UE_LOG(LogTemp, Log, TEXT("Generators: %d"), Generators.Num());
		for (auto generator : Generators)
		{
			generator->OnEnergyUpdate.AddDynamic(this, &AShield::OnShieldUpdate);
		}
	}

	OnShieldUpdate();

	HealthComponent->OnTakeDamage.AddDynamic(this, &AShield::OnTakeDamage);
}

void AShield::OnShieldUpdate()
{
	Energy = 0;
	for (auto generator : Generators) {
		Energy += generator->GetCurrentValue();
		UE_LOG(LogTemp, Log, TEXT("generator->GetCurrentValue(): %d"), generator->GetCurrentValue());
		UE_LOG(LogTemp, Log, TEXT("Energy: %d"), Energy);
	}

	//GLog->Log("Energy: " + Energy);
	UE_LOG(LogTemp, Log, TEXT("Energy: %d"), Energy);
}

void AShield::OnTakeDamage_Implementation(int health)
{
	for (int i = 0; i < Generators.Num(); ++i) {
		auto generator = Generators[i];
		if (generator->GetCurrentValue() > 0) {
			generator->ReduceEnergy();
			--Energy;
		}
	}
}
