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
	
	UPROPERTY()
	UHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Instrument, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	TSubclassOf<AWeaponProjectile> ProjectileBase;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	float FireRate;

private:

	struct FTimerHandle TimerHandle;

	UFUNCTION()
	void ShootByTimer();
};
