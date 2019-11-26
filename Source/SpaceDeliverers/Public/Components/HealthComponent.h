#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeDamage, int, Health);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeath);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	void TakeDamage(int damage);

	UPROPERTY(EditDefaultsOnly, Category = Health)
	int MaxHealth;

	FTakeDamage OnTakeDamage;
	FDeath OnDeath;

protected:
	virtual void BeginPlay() override;
	int CurrentHealth;

};
