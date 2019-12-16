#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

UCLASS()
class SPACEDELIVERERS_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponProjectile();

	FORCEINLINE void SetTargetTag(const FName& tag) { TargetTag = tag; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponProjectile, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponProjectile, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = WeaponProjectile, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY(EditDefaultsOnly)
	FName TargetTag;

	UPROPERTY(EditDefaultsOnly)
	int Damage;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* Particles;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
