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
	FORCEINLINE const BuildingType GetType() { return Type; }

	void ShowPreview(const FVector& location);
	void Build();

private:
	BuildingType Type;

};
