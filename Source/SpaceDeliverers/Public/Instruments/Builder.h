#pragma once

#include "CoreMinimal.h"
#include "Instruments/Instrument.h"
#include "Builder.generated.h"

UENUM()
enum BuildingType {
	Turret,
};

UCLASS()
class SPACEDELIVERERS_API ABuilder : public AInstrument
{
	GENERATED_BODY()

public:
	FORCEINLINE const BuildingType GetBuildingType() { return Type; }
	FORCEINLINE InstrumentType GetType() const override { return InstrumentType::Builder; }

	void ShowPreview(const FVector& location);
	void Build();

private:
	BuildingType Type;

};
