#include "Mineral.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Engine/World.h"
#include "WorldActors/Gem.h"

bool AMineral::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Wrench) {
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto gem = GetWorld()->SpawnActor<AGem>(CollectableGem, GetActorLocation(), GetActorRotation(), actorSpawnParams);
		gem->PlaySpawnAnimation(GetActorLocation());
		OnMineralHit();
		return true;
	}
	return false;
}