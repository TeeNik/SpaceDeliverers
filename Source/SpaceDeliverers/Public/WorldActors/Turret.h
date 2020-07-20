#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interactive.h"
#include "Destructible.h"
#include "Turret.generated.h"

class USoundBase;
class USpringArmComponent;
class UCameraComponent;
class UStaticMeshComponent;
class UBoxComponent;
class UArrowComponent;
class UCameraShake;
class UParticleSystemComponent;

UCLASS()
class SPACEDELIVERERS_API ATurret : public APawn, public IInteractive, public IDestructible
{
	GENERATED_BODY()

public:
	ATurret();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;
	virtual void OnSelect(class UInteractionComponent* interComp) override;
	virtual void OnDeselect() override;

	UFUNCTION(BlueprintImplementableEvent, Category = "ATurret")
	void OnDestroy();

	virtual void DestroyReached() override;
	virtual void CrashReached() override;

	void SetColliderActive(bool isActive);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float FireRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* Box;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* SmokeParticle;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UCameraShake> CameraShake;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ShootSound;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	TSubclassOf <class AWeaponProjectile> ProjectileBase;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip)
	int MaxAmmo = 10;

private:
	void Fire();
	void Release();
	APawn* ShootingPerson;
	FRotator InitialRotation;
	FVector CharacterPos;
	float LastFire;
	int CurrentAmmo;
	bool IsDestroying = false;
};
