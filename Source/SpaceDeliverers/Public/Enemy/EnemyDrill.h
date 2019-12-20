#pragma once

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "EnemyDrill.generated.h"

class UHealthComponent;

UCLASS()
class SPACEDELIVERERS_API AEnemyDrill : public AInteractiveActor
{
	GENERATED_BODY()
	
public:
	AEnemyDrill();
	virtual void BeginPlay() override;
	virtual void Interact(class AInstrument*& inHand, class ACharacter* character) override;

protected:
	UHealthComponent* HealthComponent;

private:
	UFUNCTION()
	void OnDeath(UHealthComponent* health);

};
