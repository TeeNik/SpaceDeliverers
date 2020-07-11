#pragma once

#include "CoreMinimal.h"
#include "InteractiveActor.h"
#include "ShieldGenerator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnergyUpdate);

UCLASS()
class SPACEDELIVERERS_API AShieldGenerator : public AInteractiveActor
{
	GENERATED_BODY()
public:

	AShieldGenerator();
	FORCEINLINE const float GetCurrentValue() const { return CurrentEnergy; }
	FORCEINLINE const float GetMaxValue() const { return MaxEnergy; }

	virtual bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;

	FEnergyUpdate OnEnergyUpdate;

	UPROPERTY(EditDefaultsOnly)
	float MaxEnergy = 10;

	void ReduceEnergy();

	virtual void BeginPlay() override;
	virtual void OnSelect(class UInteractionComponent* interComp) override;
	virtual void OnDeselect() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Part1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Part2;

private:
	float CurrentEnergy;

	void UpdateMaterial();
};
