#include "BuildingPlatform.h"
#include "InteractionComponent.h"
#include "Instrument.h"

void ABuildingPlatform::OnSelect(UInteractionComponent * interComp) {
	auto instrument = interComp->GetInstrument();
	if (instrument != nullptr && instrument->GetType() == InstrumentType::Builder) {
		Super::OnSelect(interComp);
		GLog->Log("Builder instrument");
		//cast to builder and show preview
	}
}

