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
	virtual void Interact(class UInteractionComponent* interComp, class ACharacter* character) override;

	FORCEINLINE class UStaticMeshComponent* GetMesh() { return Mesh; }

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnDrillHit(ACharacter* character);

protected:
	UPROPERTY(EditDefaultsOnly, Category = AEnemyDrill, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

private:
	UFUNCTION()
	void OnDeath(UHealthComponent* health);

};
