#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidSpawner.generated.h"

UCLASS()
class SPACEDELIVERERS_API AAsteroidSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	AAsteroidSpawner();

protected:
	virtual void BeginPlay() override;

	struct FTimerHandle SpawnTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<AActor>> Asteroids;

	const TArray<AActor*>* SpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float SpawnRate = 0;

	UFUNCTION()
	void Spawn();

	int AsteroidIndex = 0;
	int PointIndex = 0;

};
