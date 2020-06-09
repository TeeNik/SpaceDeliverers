#include "Builder.h"
#include "BuildingBot.h"

void ABuilder::SetInfo(ABuildingBot* bot, TSubclassOf<AActor> spawnActor)
{
	BuildingBot = bot;
	SpawnActor = spawnActor;
}
