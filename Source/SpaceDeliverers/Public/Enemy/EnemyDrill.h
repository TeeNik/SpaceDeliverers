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
	virtual bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;
	virtual float GetInteractionTime() override { return InteractionTime; }

	FORCEINLINE class UStaticMeshComponent* GetMesh() { return Mesh; }
	FORCEINLINE class UHealthComponent* GetHealthComponent() { return HealthComponent; }

	UFUNCTION(BlueprintImplementableEvent, Category = "EnemyDrill")
	void OnDrillHit(ACharacter* character, float duration);

protected:
	UPROPERTY(EditDefaultsOnly, Category = AEnemyDrill, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

private:
	UFUNCTION()
	void OnDeath(UHealthComponent* health);

};
