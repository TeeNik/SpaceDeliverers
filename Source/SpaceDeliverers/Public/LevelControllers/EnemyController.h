#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemyController.generated.h"

class AEnemyShip;
class AEnemyBot;
class UHealthComponent;
class ABuildingPlatform;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UEnemyController : public USceneComponent
{
	template<class T>
	class SpawnInfo {
		public:
			int index = -1;
			T* actor = nullptr;
	};

	GENERATED_BODY()

public:	
	UEnemyController();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Initialize();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float ShipSpawnRate;

	UPROPERTY(EditDefaultsOnly)
	float ShootRate;

	UPROPERTY(EditDefaultsOnly)
	float ShipStartDelay;

	UPROPERTY(EditDefaultsOnly)
	float BotsRate;

	UPROPERTY(EditDefaultsOnly)
	float BotsStartDelay;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyShip> EnemyShipBase;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyBot> EnemyBotBase;

private:
	const TArray<AActor*>* ShipSpawnPoints;
	int ShipsCount;
	TArray<SpawnInfo<AEnemyShip>> ShipSpawnInfo;

	const TArray<AActor*>* BotsSpawnPoints;
	AActor* GetFarthestBotPoint();
	TArray<ABuildingPlatform*> Platforms;
		
	float ShipSpawnTime;
	float ShootTime;

	float BotSpawnTime;

	bool IsShieldActive;

	UFUNCTION()
	void OnShipDeath(AEnemyShip* ship);

	UFUNCTION()
	void OnBotDeath();

	UFUNCTION()
	void OnShieldUpdate(float shield);

	void UpdateShipAttack(float seconds);
	void UpdateShipSpawn(float seconds);
	void UpdateBotSpawn(float seconds);
};
