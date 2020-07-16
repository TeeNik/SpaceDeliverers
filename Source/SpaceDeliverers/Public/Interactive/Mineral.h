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
	void OnMineralHit();

	UFUNCTION(BlueprintCallable, Category = "Mineral")
	void SpawnGem();

protected:
	UPROPERTY(EditDefaultsOnly)
	float SpawnZ = 50;

	UPROPERTY(EditDefaultsOnly)
	FVector2D SpawnGemsRange;

	//UPROPERTY(EditDefaultsOnly)
	//int GemsToSpawn = 3;

	UPROPERTY(EditDefaultsOnly)
	float Radius = 200;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGem> CollectableGem;


};
