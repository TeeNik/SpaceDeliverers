#include "Mineral.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Engine/World.h"
#include "WorldActors/Gem.h"
#include "GameFramework/Character.h"

bool AMineral::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Pickaxe) {
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


		auto dir = GetActorLocation() - character->GetActorLocation();
		float angle = FMath::RandRange(-90, 90);

		auto gem = GetWorld()->SpawnActor<AGem>(CollectableGem, GetActorLocation(), GetActorRotation(), actorSpawnParams);
		gem->PlaySpawnAnimation(GetActorLocation());
		OnMineralHit();
		return true;
	}
	return false;
}