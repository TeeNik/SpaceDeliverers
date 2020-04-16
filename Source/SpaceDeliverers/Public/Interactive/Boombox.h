#pragma once

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "Boombox.generated.h"

class UInteractionComponent;

UCLASS()
class SPACEDELIVERERS_API ABoombox : public AInteractiveActor
{
	GENERATED_BODY()

public:
	virtual bool Interact(UInteractionComponent* interComp, ACharacter* character) override;
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Boombox")
	void OnInteract(ACharacter* character);
};
