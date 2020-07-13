#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SpaceLevelScript.generated.h"

class AShieldGenerator;
class AShield;
class ABuildingBot;
class ABuildingPlatform;

UCLASS(Blueprintable)
class SPACEDELIVERERS_API ASpaceLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	FORCEINLINE TArray<AShieldGenerator*>& GetGenerators() { return Generators; }
	FORCEINLINE TArray<ABuildingPlatform*>& GetPlatforms() { return Platforms; }
	FORCEINLINE AShield* GetShield() { return Shield; }
	FORCEINLINE const TArray<AActor*>& GetShipSpawnPoints() { return ShipSpawnPoints; }
	FORCEINLINE const TArray<AActor*>& GetBotsSpawnPoints() { return BotsSpawnPoints; }
	FORCEINLINE const TArray<AActor*>& GetAsteroidSpawnPoints() { return AsteroidSpawnPoints; }
	FORCEINLINE ABuildingBot* GetBuildingBot() { return BuildingBot; }
	FORCEINLINE const AActor* GetBuildingBotHome() { return BuildingBotHome; }
	FORCEINLINE const AActor* GetPlayerCameraStart() { return PlayerCameraStartPoint; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AShieldGenerator*> Generators;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> ShipSpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> BotsSpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> AsteroidSpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AShield* Shield;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ABuildingBot* BuildingBot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AActor* BuildingBotHome;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<ABuildingPlatform*> Platforms;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AActor* PlayerCameraStartPoint;
};
