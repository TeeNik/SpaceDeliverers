#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceDeliverersCharacter.generated.h"

UCLASS(config=Game)
class ASpaceDeliverersCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
public:
	ASpaceDeliverersCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//TODO Remove weapon later
	UPROPERTY(EditAnywhere)
	bool HasWeapon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileBase;

	UPROPERTY()
	class AInstrument* Instrument;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AInstrument> WrenchBase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsProducingAction;

protected:

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	void OnFire();

	void TakeInstrument();

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};

