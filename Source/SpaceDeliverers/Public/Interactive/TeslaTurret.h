#pragma once

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "TeslaTurret.generated.h"

class AEnemyShip;
class USceneComponent;
class UParticleSystem;

UCLASS()
class SPACEDELIVERERS_API ATeslaTurret : public AInteractiveActor
{
	GENERATED_BODY()

public:
	ATeslaTurret();

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float AttackRadius;

	UPROPERTY(EditDefaultsOnly)
	float AttackRate;

	UPROPERTY(EditDefaultsOnly)
	float CheckRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SourcePoint;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* LightingParticle;

private:
	AEnemyShip* Target = nullptr;

	float LastCheck = 0;
	float LastShot = 0;

	void Attack();
	void LookForTarget();
	
};
