#include "Shield.h"
#include "ShieldGenerator.h"

AShield::AShield()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AShield::BeginPlay()
{
	Super::BeginPlay();

	/*for(auto generator : Generators)
	{
		generator->OnEnergyUpdate.AddDynamic(this, &AShield::OnShieldUpdate);
	}*/
}

void AShield::OnShieldUpdate()
{

}
