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

		int dispersion = 90;
		FVector actorLoc = GetActorLocation();
		auto offset = actorLoc - character->GetActorLocation();
		offset.Z = 0;
		int angle = FMath::RandRange(-dispersion, dispersion);
		offset = offset.RotateAngleAxis(angle, FVector(0, 0, 1));
		offset.Normalize();
		offset *= Radius;

		auto gem = GetWorld()->SpawnActor<AGem>(CollectableGem, actorLoc, GetActorRotation(), actorSpawnParams);
		gem->PlaySpawnAnimation(actorLoc, offset);
		OnMineralHit();
		return true;
	}
	return false;
}