#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "SpaceLevelScript.generated.h"

class AShieldGenerator;
class AShield;

UCLASS(Blueprintable)
class SPACEDELIVERERS_API ASpaceLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	FORCEINLINE TArray<AShieldGenerator*>& GetGenerators() { return Generators; }
	FORCEINLINE AShield* GetShield() { return Shield; }
	FORCEINLINE TArray<AActor*>& GetShipSpawnPoints() { return ShipSpawnPoints; }
	FORCEINLINE TArray<AActor*>& GetAsteroidSpawnPoints() { return AsteroidSpawnPoints; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AShieldGenerator*> Generators;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> ShipSpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<AActor*> AsteroidSpawnPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	AShield* Shield;
};
