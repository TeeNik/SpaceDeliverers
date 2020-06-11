#include "Builder.h"
#include "BuildingBot.h"

void ABuilder::SetSpawnActor(TSubclassOf<AActor> spawnActor)
{
	SpawnActor = spawnActor;
}
