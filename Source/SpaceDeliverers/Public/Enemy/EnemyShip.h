#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemyShip.generated.h"

class UHealthComponent;

UCLASS()
class SPACEDELIVERERS_API AEnemyShip : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemyShip();

	FORCEINLINE const UHealthComponent* GetHealthComponent() { return HealthComponent; }

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	UHealthComponent* HealthComponent;

};
