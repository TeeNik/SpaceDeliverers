#include "Boombox.h"
#include "Instrument.h"
#include "GameFramework/Character.h"
#include "InteractionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

bool ABoombox::Interact(UInteractionComponent* interComp, ACharacter* character) {
	if (interComp->GetInstrument() == NULL)
	{
		OnInteract(character);
		if (Audio == nullptr) {
			Audio = UGameplayStatics::SpawnSoundAtLocation(this, Music, GetActorLocation());
		}
		if (Audio->IsPlaying()) {
			Audio->Play();
		}
		else {
			Audio->Stop();
		}
		return true;
	}
	return false;
}