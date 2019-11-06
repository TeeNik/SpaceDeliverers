#pragma once

#include "CoreMinimal.h"
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

	virtual void Interact(class AInstrument* inHand, class ACharacter* character) {}
	virtual void OnSelect();
	virtual void OnDeselect();
};