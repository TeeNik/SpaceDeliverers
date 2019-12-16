#include "EnemyController.h"
#include "Engine/World.h"
#include "SpaceLevelScript.h"
#include "EnemyShip.h"
#include "HealthComponent.h"

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
	int num = Ships.Num();
	if (num > 0 && seconds > ShootTime)
	{
		int index = FMath::RandRange(0, num - 1);
		UE_LOG(LogTemp, Log, TEXT("Index Rand: %d"), index);
		ShootTime = seconds + ShootRate;
		Ships[index]->Shoot();
	}
	if (num < SpawnPoints->Num() && seconds > SpawnTime)
	{
		int index = -1;
		SpawnInfo.Find(false, index);
		if (index >= 0) {
			AActor* point = (*SpawnPoints)[index];
			FVector position = point->GetActorLocation();
			FRotator rotation = point->GetActorRotation();
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AEnemyShip* enemy = GetWorld()->SpawnActor<AEnemyShip>(EnemyShipBase, position, rotation, ActorSpawnParams);
			Ships.Add(enemy);
			SpawnTime = seconds + SpawnRate;
			enemy->GetHealthComponent()->OnDeath.AddDynamic(this, &UEnemyController::OnShipDeath);
		}
	}
}

void UEnemyController::OnShipDeath(UHealthComponent* hc)
{
	AEnemyShip* ship = Cast<AEnemyShip>(hc->GetOwner());
	Ships.Remove(ship);
	ship->Destroy();
}