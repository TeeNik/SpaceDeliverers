#include "Shield.h"
#include "ShieldGenerator.h"
#include "System/SpaceLevelScript.h"

AShield::AShield()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
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
}

void AShield::OnShieldUpdate()
{

}
