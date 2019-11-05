#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

class IInteractive {

	GENERATED_BODY()

public:

	virtual void OnInteract(class AInstrument* inHand) {}

};
