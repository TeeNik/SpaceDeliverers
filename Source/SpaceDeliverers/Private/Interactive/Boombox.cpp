#include "Boombox.h"
#include "Instrument.h"
#include "GameFramework/Character.h"
#include "InteractionComponent.h"

bool ABoombox::Interact(UInteractionComponent* interComp, ACharacter* character) {
	if (interComp->GetInstrument() == NULL)
	{
		GLog->Log("ABoombox::Interact");
		OnInteract(character);
		return true;
	}
	return false;
}