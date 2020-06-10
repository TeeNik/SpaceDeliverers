#pragma once

#include "CoreMinimal.h"
#include "Instruments/Instrument.h"
#include "Builder.generated.h"

UCLASS()
class SPACEDELIVERERS_API ABuilder : public AInstrument
{
	GENERATED_BODY()

public:
	FORCEINLINE InstrumentType GetType() const override { return InstrumentType::Builder; }
	FORCEINLINE const TSubclassOf<AActor> GetSpawningActor() const { return SpawnActor; }

	void SetSpawnActor(TSubclassOf<AActor> spawnActor);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SpawnActor;
};
