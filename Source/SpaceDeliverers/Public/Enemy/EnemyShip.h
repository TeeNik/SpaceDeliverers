#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyShip.generated.h"

class UHealthComponent;
class AWeaponProjectile;
class UParticleSystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShipDeath, AEnemyShip*, ship);

UCLASS()
class SPACEDELIVERERS_API AEnemyShip : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyShip();

	FORCEINLINE UHealthComponent* GetHealthComponent() { return HealthComponent; }

	UFUNCTION(BlueprintImplementableEvent, Category = "EnemyShip")
	void OnSpawn();

	void Shoot();
	UFUNCTION(BlueprintCallable)
	void StartMovement();

	UPROPERTY(BlueprintAssignable)
	FShipDeath OnDeathCallback;


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	TSubclassOf<AWeaponProjectile> ProjectileBase;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	float FireRate;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	float XValue;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	float YValue;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	float ZValue;

	UFUNCTION()
	void OnDeath();

private:

	bool IsMovementAble;
	float RunningTime;

	struct FTimerHandle TimerHandle;

	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditDefaultsOnly)
	FVector ParticleSize;
};
