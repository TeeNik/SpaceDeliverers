#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SpaceLevelScript.generated.h"

class AShieldGenerator;
class AShield;
class ABuildingBot;

UCLASS(Blueprintable)
class SPACEDELIVERERS_API ASpaceLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	FORCEINLINE TArray<AShieldGenerator*>& GetGenerators() { return Generators; }
	FORCEINLINE AShield* GetShield() { return Shield; }
	FORCEINLINE const TArray<AActor*>& GetShipSpawnPoints() { return ShipSpawnPoints; }
	FORCEINLINE const TArray<AActor*>& GetAsteroidSpawnPoints() { return AsteroidSpawnPoints; }
	FORCEINLINE ABuildingBot* GetBuildingBot() { return BuildingBot; }
	FORCEINLINE const AActor* GetBuildingBotHome() { return BuildingBotHome; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AShieldGenerator*> Generators;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> ShipSpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> AsteroidSpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AShield* Shield;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	ABuildingBot* BuildingBot;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AActor* BuildingBotHome;
};
