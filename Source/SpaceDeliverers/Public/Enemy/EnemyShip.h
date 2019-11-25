#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyShip.generated.h"

class UHealthComponent;
class AWeaponProjectile;

UCLASS()
class SPACEDELIVERERS_API AEnemyShip : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyShip();

	FORCEINLINE const UHealthComponent* GetHealthComponent() { return HealthComponent; }


protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
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

private:

	float RunningTime;

	struct FTimerHandle TimerHandle;

	UFUNCTION()
	void ShootByTimer();

	UFUNCTION()
	void OnTakeDamage(int health);
};
