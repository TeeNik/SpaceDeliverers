#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FShieldUpdate, float, Shield);

UCLASS()
class SPACEDELIVERERS_API AShield : public AActor
{
	GENERATED_BODY()
	
public:	
	AShield();
	FShieldUpdate OnShieldUpdate;

	void Initialize();

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
	void OnTakeDamage(int health, UHealthComponent* hc);

	float CurrentEnergy;
	float MaxEnergy;
};
