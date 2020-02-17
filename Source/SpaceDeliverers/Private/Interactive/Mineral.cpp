#include "Mineral.h"
#include "InteractionComponent.h"
#include "Instrument.h"

bool AMineral::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Wrench) {
		OnMineralHit(character, InteractionTime);
		return true;
	}
	return false;
}