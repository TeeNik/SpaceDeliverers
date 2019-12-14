#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemyController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UEnemyController : public USceneComponent
{
	GENERATED_BODY()

public:	
	UEnemyController();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float SpawnRate;

	UPROPERTY(EditDefaultsOnly)
	float ShootRate;

	UPROPERTY(EditDefaultsOnly)
	float StartDelay;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyShip> EnemyShipBase;

private:
	TArray<AActor*>* SpawnPoints;
	TArray<AEnemyShip*> Ships;
	int NumberOfEnemies;
	TArray<bool> SpawnInfo;
		
	float SpawnTime;
	float ShootTime;

	UFUNCTION()
	void OnShipTakeDamage(int health);
};
