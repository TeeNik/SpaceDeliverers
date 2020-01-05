#include "EnemyController.h"
#include "Engine/World.h"
#include "SpaceLevelScript.h"
#include "EnemyShip.h"
#include "EnemyDrill.h"
#include "HealthComponent.h"
#include "Shield.h"

UEnemyController::UEnemyController()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UEnemyController::BeginPlay()
{
	Super::BeginPlay();
}

void UEnemyController::Initialize()
{
	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	ShipSpawnPoints = &level->GetSpawnPoints();
	ShipSpawnInfo.SetNum(ShipSpawnPoints->Num());
	level->GetShield()->OnShieldUpdate.AddDynamic(this, &UEnemyController::OnShieldUpdate);

	ShipSpawnTime = ShipStartDelay;
	ShootTime = ShipStartDelay;
}

void UEnemyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float seconds = GetWorld()->GetTimeSeconds();

	if (IsShieldActive) 
	{
		if (ShipsCount > 0 && seconds > ShootTime)
		{
			int index = FMath::RandRange(0, ShipsCount - 1);
			UE_LOG(LogTemp, Log, TEXT("Index Rand: %d"), index);
			ShootTime = seconds + ShootRate;
			ShipSpawnInfo[index].actor->Shoot();
		}
		if (ShipsCount < ShipSpawnPoints->Num() && seconds > ShipSpawnTime)
		{
			int index = -1;
			for (int i = 0; i < ShipSpawnInfo.Num(); ++i) {
				if (ShipSpawnInfo[i].actor == nullptr) {
					index = i;
					break;
				}
			}
			if (index >= 0) {
				AActor* point = (*ShipSpawnPoints)[index];
				FVector position = point->GetActorLocation();
				FRotator rotation = point->GetActorRotation();
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AEnemyShip* enemy = GetWorld()->SpawnActor<AEnemyShip>(EnemyShipBase, position, rotation, ActorSpawnParams);
				ShipSpawnTime = seconds + ShipSpawnRate;
				ShipSpawnInfo[index].actor = enemy;
				ShipSpawnInfo[index].index = index;
				enemy->GetHealthComponent()->OnDeath.AddDynamic(this, &UEnemyController::OnShipDeath);
			}
		}
	}
	else {
		return;
		int num = Drills.Num();

		if (num > 0 && seconds > DrillTime) {
			//send take damage to base controller
		}
		//TODO move to function
		if (num < DrillSpawnPoints->Num() && seconds > DrillSpawnTime) {
			int index = -1;
			DrillSpawnInfo.Find(false, index);
			if (index >= 0) {
				AActor* point = (*DrillSpawnPoints)[index];
				FVector position = point->GetActorLocation();
				FRotator rotation = point->GetActorRotation();
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AEnemyDrill* enemy = GetWorld()->SpawnActor<AEnemyDrill>(EnemyDrillBase, position, rotation, ActorSpawnParams);
				Drills.Add(enemy);
				DrillSpawnTime = seconds + ShipSpawnRate;
				enemy->GetHealthComponent()->OnDeath.AddDynamic(this, &UEnemyController::OnDrillDeath);
			}
		}
	}
}

//inline? how does inline func work in loop?

template<class T>
T* SpawnActor(TArray<T*>& container, int& spawnTime, TArray<AActor*>* spawnPoints, TArray<bool>& info, TSubclassOf<T> spawnClass)
{
	int num = container.Num();
	if (num < info.Num() && seconds > SpawnTime) {
		int index = info.Find(false);
		if (index >= 0) {
			AActor* point = (*spawnPoints)[index];
			FVector position = point->GetActorLocation();
			FRotator rotation = point->GetActorRotation();
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			T* enemy = GetWorld()->SpawnActor<T>(spawnClass, position, rotation, ActorSpawnParams);
			container.Add(enemy);
			return enemy;
		}
	}
	return NULL;
}

void UEnemyController::OnShipDeath(UHealthComponent* hc)
{
	ShipSpawnTime += ShipSpawnRate;
	AEnemyShip* ship = Cast<AEnemyShip>(hc->GetOwner());
	for (auto& info : ShipSpawnInfo) {
		if (info.actor == ship) {
			info.actor = nullptr;
			info.index = -1;
		}
	}
	ship->Destroy();
}

void UEnemyController::OnDrillDeath(UHealthComponent * hc)
{
	AEnemyDrill* drill = Cast<AEnemyDrill>(hc->GetOwner());
	Drills.Remove(drill);
	drill->Destroy();
}

void UEnemyController::OnShieldUpdate(float shield)
{
	IsShieldActive = shield > 0;
}
