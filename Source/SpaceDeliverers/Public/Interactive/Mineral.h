#pragma once;

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "Mineral.generated.h"

UCLASS()
class SPACEDELIVERERS_API AMineral : public AInteractiveActor
{
	GENERATED_BODY()

public:

	virtual bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;
	virtual float GetInteractionTime() override { return InteractionTime; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Mineral")
	void OnMineralHit(ACharacter* character, AActor* collectable, float x, float y, float duration);

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Height;

protected:

	UPROPERTY(EditDefaultsOnly)
	float InteractionTime = 3;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> CollectableActor;

	UPROPERTY(EditDefaultsOnly)
	float Radius;

};
