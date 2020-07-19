#include "Mineral.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Engine/World.h"
#include "WorldActors/Gem.h"
#include "GameFramework/Character.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

bool AMineral::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Pickaxe) 
	{
		OnMineralHit();
		return true;
	}
	return false;
}

void AMineral::SpawnGem()
{
	FActorSpawnParameters actorSpawnParams;
	actorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	int dispersion = 90;
	FVector actorLoc = GetActorLocation();
	ACharacter* owner = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);;

	int gemsToSpawn = FMath::RandRange(SpawnGemsRange.X, SpawnGemsRange.Y);

	for (int i = 0; i < gemsToSpawn; ++i)
	{
		auto offset = actorLoc - owner->GetActorLocation();
		offset.Z = 0;
		int angle = FMath::RandRange(-dispersion, dispersion);
		offset = offset.RotateAngleAxis(angle, FVector(0, 0, 1));
		offset.Normalize();
		offset *= Radius;

		actorLoc.Z = SpawnZ;

		auto gem = GetWorld()->SpawnActor<AGem>(CollectableGem, actorLoc, GetActorRotation(), actorSpawnParams);
		gem->PlaySpawnAnimation(actorLoc, offset);
	}
}
