#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "Toolbox.generated.h"


UCLASS()
class SPACEDELIVERERS_API AToolbox : public AInteractive
{
	GENERATED_BODY()
	
public:	
	AToolbox();

	void Interact(class AInstrument* inHand, class ACharacter* character) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AWrench> WrenchBase;
};
