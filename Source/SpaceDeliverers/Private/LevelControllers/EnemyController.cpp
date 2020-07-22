#include "EnemyController.h"
#include "Engine/World.h"
#include "SpaceLevelScript.h"
#include "EnemyShip.h"
#include "EnemyBot.h"
#include "HealthComponent.h"
#include "Shield.h"
#include "BuildingPlatform.h"

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
	ShipSpawnPoints = &level->GetShipSpawnPoints();
	BotsSpawnPoints = &level->GetBotsSpawnPoints();
	ShipSpawnInfo.SetNum(ShipSpawnPoints->Num());
	level->GetShield()->OnShieldUpdate.AddDynamic(this, &UEnemyController::OnShieldUpdate);
	Platforms = level->GetPlatforms();
	ShipSpawnTime = ShipStartDelay;
	ShootTime = ShipStartDelay;
	BotSpawnTime = BotsStartDelay;
}

void UEnemyController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float seconds = GetWorld()->GetTimeSeconds();

	UpdateShipAttack(seconds);
	UpdateShipSpawn(seconds);
	UpdateBotSpawn(seconds);

}

AActor* UEnemyController::GetFarthestBotPoint() {
	AActor* finalPoint = nullptr;
	float finalDist = 0;
	FVector playerPos = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation();

	for (auto point : (*BotsSpawnPoints)) {
		float dist = FVector::DistSquared(point->GetActorLocation(), playerPos);
		if (dist > finalDist) {
			finalDist = dist;
			finalPoint = point;
		}
	}
	return finalPoint;
}

void UEnemyController::UpdateShipAttack(float seconds)
{
	if (ShipsCount > 0 && seconds > ShootTime)
	{
		for (auto& info : ShipSpawnInfo) {
			if (info.actor != nullptr) {
				info.actor->Shoot();
				break;
			}
		}
		ShootTime = seconds + ShootRate;
	}
}

void UEnemyController::UpdateShipSpawn(float seconds)
{
	if (ShipsCount < ShipSpawnPoints->Num() && seconds > ShipSpawnTime)
	{
		++ShipsCount;
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
			enemy->OnDeathCallback.AddDynamic(this, &UEnemyController::OnShipDeath);
			enemy->OnSpawn();
		}
	}
}

void UEnemyController::UpdateBotSpawn(float seconds)
{
	bool hasFreeTargets = false;
	for (auto* platform : Platforms)
	{
		if (!platform->IsFree() && !platform->IsBotTarget 
								&& !platform->GetIsBuildingProcess()
								&& seconds > BotSpawnTime)
		{
			AActor* point = GetFarthestBotPoint();
			FVector position = point->GetActorLocation();
			FRotator rotation = point->GetActorRotation();
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AEnemyBot* bot = GetWorld()->SpawnActor<AEnemyBot>(EnemyBotBase, position, rotation, ActorSpawnParams);
			bot->SpawnDefaultController();
			bot->SetTargetPlatform(platform);
			float time = FMath::RandRange(BotSpawnRange.X, BotSpawnRange.Y);
			BotSpawnTime = seconds + time;
			break;
		}
	}
}

void UEnemyController::OnShipDeath(AEnemyShip* ship)
{
	ShipSpawnTime = GetWorld()->GetTimeSeconds() + ShipSpawnRate;
	for (auto& info : ShipSpawnInfo) {
		if (info.actor == ship) {
			info.actor = nullptr;
			info.index = -1;
		}
	}
	--ShipsCount;
}

void UEnemyController::OnBotDeath()
{
	BotSpawnTime = GetWorld()->GetTimeSeconds() + FMath::RandRange(BotSpawnRange.X, BotSpawnRange.Y);
}

void UEnemyController::OnShieldUpdate(float shield)
{
	IsShieldActive = shield > 0;
}
