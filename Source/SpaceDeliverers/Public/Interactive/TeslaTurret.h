#pragma once

#include "CoreMinimal.h"
#include "Interactive/InteractiveActor.h"
#include "Destructible.h"
#include "TeslaTurret.generated.h"

class AEnemyShip;
class USceneComponent;
class UParticleSystem;

UCLASS()
class SPACEDELIVERERS_API ATeslaTurret : public AInteractiveActor, public IDestructible
{
	GENERATED_BODY()

public:
	ATeslaTurret();

	virtual void DestroyReached() override;

protected:
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly)
	float AttackRadius;

	UPROPERTY(EditDefaultsOnly)
	float AttackRate;

	UPROPERTY(EditDefaultsOnly)
	float CheckRate;

	UPROPERTY(EditDefaultsOnly)
	float LightningDuration;

	UPROPERTY(EditDefaultsOnly)
	float Damage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	USceneComponent* SourcePoint;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* LightingParticle;

private:
	AEnemyShip* Target = nullptr;
	UParticleSystemComponent* lightning = nullptr;

	TArray<FHitResult> GetActorsInRange(float radius);

	UFUNCTION()
	void OnTargetDestroy(AEnemyShip* ship);

	float LastCheck = 0;
	float LastAttack = 0;
	float LightningDestroyTime = 0;

	void Attack();
	void LookForTarget();
};