#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactive/Interactive.h"
#include "ShieldGenerator.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEnergyUpdate);

UCLASS()
class SPACEDELIVERERS_API AShieldGenerator : public AActor, public IInteractive
{
	GENERATED_BODY()
public:

	AShieldGenerator();
	FORCEINLINE const float GetCurrentValue() const { return CurrentEnergy / MaxEnergy; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	virtual void Interact(class AInstrument*& inHand, const class ACharacter* character) override;
	virtual void OnSelect() override{};
	virtual void OnDeselect() override {};

	FEnergyUpdate OnEnergyUpdate;

	UPROPERTY(EditDefaultsOnly)
	int MaxEnergy = 10;

	void ReduceEnergy();

	virtual void BeginPlay() override;

private:
	int CurrentEnergy;

	void UpdateMaterial();
};
