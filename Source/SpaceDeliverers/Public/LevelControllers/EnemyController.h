#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "EnemyController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SPACEDELIVERERS_API UEnemyController : public USceneComponent
{
	GENERATED_BODY()

public:	
	UEnemyController();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float SpawnRate;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AEnemyShip> EnemeShipBase;

private:
	TArray<AActor*>* SpawnPoints;
	TArray<bool> SpawnInfo;
	float LastSpawnTime;
		
};
