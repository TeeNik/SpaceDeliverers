#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FTakeDamage, int, Health, UHealthComponent*, Component);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeath, UHealthComponent*, Component);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	FORCEINLINE int GetCurrentHealth() { return CurrentHealth; }
	void TakeDamage(int damage);
	UPROPERTY(EditDefaultsOnly, Category = Health)
	int MaxHealth;
	FTakeDamage OnTakeDamage;
	FDeath OnDeath;

protected:
	virtual void BeginPlay() override;
	int CurrentHealth;

};
