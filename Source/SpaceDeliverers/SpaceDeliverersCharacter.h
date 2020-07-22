#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpaceDeliverersCharacter.generated.h"

enum InstrumentType;

UCLASS(config=Game)
class ASpaceDeliverersCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* InteractionBox;

public:
	ASpaceDeliverersCharacter();

	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE class UInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> ProjectileBase;

	UFUNCTION(BlueprintImplementableEvent, Category = "Character")
	void OnFireBP(InstrumentType type);

	void ScaleInteractionBox(const int& coeff);

	UFUNCTION(BlueprintImplementableEvent)
	void DisableMovement(float time);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInventoryComponent* InventoryComponent;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
	bool IsRotationEnabled = true;

	void OnFire();
	void OnRelease();
	virtual void BeginPlay() override;
	void OnEscPressed();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION()
	void OnInstrumentChanged(int type);

private:

	UPROPERTY(EditDefaultsOnly)
	bool IsNeedCameraAnimation;

	UPROPERTY(EditDefaultsOnly)
	float CameraAnimationDuration;

	void StartCameraAnimation();

	UFUNCTION()
	void OnCameraAnimationEnd();

	int InteractionBoxScaleFactor = 1;
	const float BoxOffset = 75;
};

