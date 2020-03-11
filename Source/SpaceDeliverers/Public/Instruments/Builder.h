#pragma once

#include "CoreMinimal.h"
#include "Instruments/Instrument.h"
#include "Builder.generated.h"

UENUM()
enum BuildingType {
	Turret,
};

class ABuildingBot;


UCLASS()
class SPACEDELIVERERS_API ABuilder : public AInstrument
{
	GENERATED_BODY()

public:
	FORCEINLINE const BuildingType GetBuildingType() { return Type; }
	FORCEINLINE InstrumentType GetType() const override { return InstrumentType::Builder; }
	FORCEINLINE const TSubclassOf<AActor> GetSpawningActor() const { return SpawnActor; }

	void ShowPreview(const FVector& location);
	void Build();
	void SetInfo(ABuildingBot* bot);

protected:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> SpawnActor;

private:
	BuildingType Type;
	ABuildingBot* BuildingBot = nullptr;
};
