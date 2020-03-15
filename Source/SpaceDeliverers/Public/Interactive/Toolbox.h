#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "Toolbox.generated.h"


UCLASS()
class SPACEDELIVERERS_API AToolbox : public AInteractiveActor
{
	GENERATED_BODY()
	
public:	
	AToolbox();

	bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AInstrument> InstrumentBase;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName AttachSocket;
};
