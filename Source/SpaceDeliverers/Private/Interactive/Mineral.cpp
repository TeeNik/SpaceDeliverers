#include "Mineral.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Engine/World.h"

bool AMineral::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Wrench) {
		FActorSpawnParameters actorSpawnParams;
		actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		auto collectable = GetWorld()->SpawnActor<AActor>(CollectableActor, GetActorLocation(), GetActorRotation(), actorSpawnParams);
		float x = FMath::Cos(FMath::RandRange(0, 360)) * Radius;
		float y = FMath::Sin(FMath::RandRange(0, 360)) * Radius;
		OnMineralHit(character, collectable, x, y, InteractionTime);
		return true;
	}
	return false;
}