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

	virtual void Interact(class UInteractionComponent* interComp, class ACharacter* character) override;

	FEnergyUpdate OnEnergyUpdate;

	UPROPERTY(EditDefaultsOnly)
	float MaxEnergy = 10;

	void ReduceEnergy();

	virtual void BeginPlay() override;

private:
	float CurrentEnergy;

	void UpdateMaterial();
};
