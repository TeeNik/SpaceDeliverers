#include "ShieldGenerator.h"
#include "Instrument.h"

void AShieldGenerator::Interact(class AInstrument * inHand, const class ACharacter* character) {

	if (inHand != NULL) {
		if (inHand->GetType() == InstrumentType::Wrench) {
			if (CurrentEnergy < MaxEnergy) {
				++CurrentEnergy;
				OnEnergyUpdate.Broadcast();
			}
		}
	}

}

void AShieldGenerator::UpdateMaterial()
{

}
