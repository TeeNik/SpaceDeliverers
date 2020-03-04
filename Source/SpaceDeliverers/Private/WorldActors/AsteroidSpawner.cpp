#include "AsteroidSpawner.h"
#include "TimerManager.h"
#include "Engine\World.h"
#include "SpaceLevelScript.h"

AAsteroidSpawner::AAsteroidSpawner()
{
}

void AAsteroidSpawner::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("AAsteroidSpawner: BeginPlay"));
	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	SpawnPoints = &level->GetAsteroidSpawnPoints();

	if (Asteroids.Num() > 0 && SpawnPoints->Num() > 0) {
		UE_LOG(LogTemp, Log, TEXT("InitTimer"));
		GetWorld()->GetTimerManager().SetTimer(SpawnTimer, this, &AAsteroidSpawner::Spawn, SpawnRate, true);
	}
}

void AAsteroidSpawner::Spawn()
{
	UE_LOG(LogTemp, Log, TEXT("AAsteroidSpawner::Spawn"));
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	auto location = (*SpawnPoints)[PointIndex]->GetActorLocation();
	auto rotation = (*SpawnPoints)[PointIndex]->GetActorRotation();
	auto actor = GetWorld()->SpawnActor<AActor>(Asteroids[AsteroidIndex], location, rotation, ActorSpawnParams);

	PointIndex = (PointIndex + 1) % SpawnPoints->Num();
	AsteroidIndex = (AsteroidIndex + 1) % Asteroids.Num();
}