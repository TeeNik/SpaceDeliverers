#pragma once

/*#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive.generated.h"

UCLASS()
class SPACEDELIVERERS_API AInteractive : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Instrument, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

public:
	AInteractive();

	virtual void Interact(class AInstrument*& inHand, const class ACharacter* character) {}
	virtual void OnSelect();
	virtual void OnDeselect();
};*/

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactive.generated.h"

UINTERFACE(MinimalAPI, meta = (CannotImplementInterfaceInBlueprint))
class SPACEDELIVERERS_API UInteractive : public UInterface
{
	GENERATED_BODY()
};

class IInteractive {

	GENERATED_BODY()

public:

	virtual void Interact(class AInstrument*& inHand, const class ACharacter* character) {}
	virtual void OnSelect() {};
	virtual void OnDeselect() {};
};