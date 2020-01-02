#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemyController.generated.h"

class AEnemyShip;
class AEnemyDrill;
class UHealthComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UEnemyController : public USceneComponent
{
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
	float DrillRate;

	UPROPERTY(EditDefaultsOnly)
	float DrillStartDelay;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyShip> EnemyShipBase;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AEnemyDrill> EnemyDrillBase;

private:
	TArray<AActor*>* ShipSpawnPoints;
	TArray<AEnemyShip*> Ships;
	TArray<bool> ShipSpawnInfo;

	TArray<AActor*>* DrillSpawnPoints;
	TArray<AEnemyDrill*> Drills;
	TArray<bool> DrillSpawnInfo;
		
	float ShipSpawnTime;
	float ShootTime;

	float DrillSpawnTime;
	float DrillTime;

	bool IsShieldActive;

	UFUNCTION()
	void OnShipDeath(UHealthComponent* hc);

	UFUNCTION()
	void OnDrillDeath(UHealthComponent* hc);

	UFUNCTION()
	void OnShieldUpdate(float shield);
};
