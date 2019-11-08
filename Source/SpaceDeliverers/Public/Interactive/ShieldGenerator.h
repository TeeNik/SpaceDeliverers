#pragma once

#include "CoreMinimal.h"
#include "Interactive/Interactive.h"
#include "ShieldGenerator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnergyUpdate);

UCLASS()
class SPACEDELIVERERS_API AShieldGenerator : public AInteractive
{
	GENERATED_BODY()
public:

	FORCEINLINE const float GetCurrentValue() const { return CurrentEnergy / MaxEnergy; }
	virtual void Interact(class AInstrument*& inHand, const class ACharacter* character) override;

	FEnergyUpdate OnEnergyUpdate;

	UPROPERTY(EditDefaultsOnly)
	int MaxEnergy = 10;


private:
	int CurrentEnergy;

	void UpdateMaterial();
};
