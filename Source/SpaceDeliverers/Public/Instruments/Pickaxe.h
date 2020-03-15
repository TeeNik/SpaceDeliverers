#pragma once

#include "CoreMinimal.h"
#include "Instruments/Instrument.h"
#include "Pickaxe.generated.h"

UCLASS()
class SPACEDELIVERERS_API APickaxe : public AInstrument
{
	GENERATED_BODY()

public:
	virtual InstrumentType GetType() const override;
};
