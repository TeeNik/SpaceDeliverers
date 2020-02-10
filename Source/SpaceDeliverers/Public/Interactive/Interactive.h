#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"

UINTERFACE()
class UInteractive : public UInterface
{
	GENERATED_BODY()
};

class IInteractive {

	GENERATED_BODY()

public:

	//virtual void Interact(class UInteractionComponent* interComp, class ACharacter* character) {}
	virtual bool Interact(class UInteractionComponent* interComp, class ACharacter* character) { return false; }
	virtual float GetInteractionTime() { return 0; }
	virtual void OnSelect(class UInteractionComponent* interComp) {};
	virtual void OnDeselect() {};
};