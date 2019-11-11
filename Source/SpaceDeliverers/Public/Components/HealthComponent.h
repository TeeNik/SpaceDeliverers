#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTakeDamage, int, Health);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	void TakeDamage(int damage);

	UPROPERTY()
	int MaxHealth;

	FTakeDamage OnTakeDamage;

protected:
	virtual void BeginPlay() override;
	int CurrentHealth;

};
