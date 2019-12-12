#include "EnemyController.h"
#include "Engine/World.h"
#include "SpaceLevelScript.h"
#include "EnemyShip.h"

UEnemyController::UEnemyController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Log, TEXT("UEnemyController::BeginPlay"));

	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	SpawnPoints = &level->GetSpawnPoints();
	SpawnInfo.SetNum(SpawnPoints->Num());

	SpawnTime = StartDelay;
	ShootTime = StartDelay;
}

void UEnemyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float seconds = GetWorld()->GetTimeSeconds();
	if (NumberOfEnemies > 0 && seconds > ShootTime)
	{
		int index = FMath::RandRange(0, NumberOfEnemies - 1);
		UE_LOG(LogTemp, Log, TEXT("Index Rand: %d", index));
		//Ships[index]->Shoot();
	}
	if (NumberOfEnemies < SpawnPoints->Num() && seconds > SpawnTime) 
	{
		int index = -1;
		SpawnInfo.Find(false, index);
		if (index >= 0) {
			++NumberOfEnemies;
			AActor* point = (*SpawnPoints)[index];
			FVector position = point->GetActorLocation();
			FRotator rotation = point->GetActorRotation();
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AEnemyShip* enemy = GetWorld()->SpawnActor<AEnemyShip>(EnemyShipBase, position, rotation, ActorSpawnParams);
			SpawnTime = seconds + SpawnRate;
		}
	}
}

