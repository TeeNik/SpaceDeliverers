#pragma once

#include "CoreMinimal.h"
#include "Instruments/Instrument.h"
#include "Wrench.generated.h"

UCLASS()
class SPACEDELIVERERS_API AWrench : public AInstrument
{
	GENERATED_BODY()

public:
	virtual void Use() override;
	virtual InstrumentType GetType() const override;
	
};
