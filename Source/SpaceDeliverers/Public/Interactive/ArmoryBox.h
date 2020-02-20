#pragma once

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "ArmoryBox.generated.h"

UCLASS()
class SPACEDELIVERERS_API AArmoryBox : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AGun> GunBase;
};
