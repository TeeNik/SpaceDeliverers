#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shield.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FShieldUpdate, int, Shield);

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
	void OnShieldUpdate();

	TArray<class AShieldGenerator*>* Generators;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Character")
	void OnTakeDamageBP(int health);

	UFUNCTION()
	void OnTakeDamage(int health);

	int Energy;
};
