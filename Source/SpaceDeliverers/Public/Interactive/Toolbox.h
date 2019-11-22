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

	void Interact(class AInstrument*& inHand, const class ACharacter* character) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AWrench> WrenchBase;
};
