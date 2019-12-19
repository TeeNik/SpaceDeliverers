#include "Instrument.h"
#include "..\..\Public\Instruments\Instrument.h"

AInstrument::AInstrument()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

}

void AInstrument::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInstrument::Use()
{
}

InstrumentType AInstrument::GetType() const
{
	return InstrumentType::None;
}

void AInstrument::Release()
{
	FDetachmentTransformRules rules(EDetachmentRule::KeepWorld, false);
	DetachFromActor(rules);
}
