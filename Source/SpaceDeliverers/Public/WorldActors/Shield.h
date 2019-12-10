#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FShieldUpdate, float );

UCLASS()
class SPACEDELIVERERS_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	AShield();
	FShieldUpdate OnShieldUpdate;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Instrument, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	virtual void BeginPlay() override;

	UPROPERTY()
	class UHealthComponent* HealthComponent;

	UFUNCTION()
	void OnGeneratorEnergyUpdate();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character")
	void OnTakeDamageBP(int health);

private:
	void BroadcastShieldPercent();

	TArray<class AShieldGenerator*>* Generators;

	UFUNCTION()
	void OnTakeDamage(int health);

	float CurrentEnergy;
	float MaxEnergy;
};
