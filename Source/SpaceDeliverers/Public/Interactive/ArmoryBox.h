#pragma once

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "ArmoryBox.generated.h"

UCLASS()
class SPACEDELIVERERS_API AArmoryBox : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	AArmoryBox();

	void Interact(class AInstrument*& inHand, class ACharacter* character) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class AGun> GunBase;
};
