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
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AWrench> WrenchBase;
};
