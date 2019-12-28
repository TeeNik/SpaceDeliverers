#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Interactive.h"
#include "Turret.generated.h"

UCLASS()
class SPACEDELIVERERS_API ATurret : public APawn, public IInteractive
{
	GENERATED_BODY()

public:
	ATurret();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float FireRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box;

	UPROPERTY(EditDefaultsOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	TSubclassOf <class AWeaponProjectile> ProjectileBase;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnSelect() override;
	virtual void OnDeselect() override;
	void Interact(class UInteractionComponent* interComp, class ACharacter* character) override;

private:
	void Fire();
	void Release();
	APawn* ShootingPerson;
	FRotator InitialRotation;
	FVector CharacterPos;
	float LastFire;
	const FName TargetTag = "EnemyShip";
};
