#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceDeliverersGameMode.generated.h"

class UBaseController;
class UEnemyController;

UCLASS(minimalapi)
class ASpaceDeliverersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceDeliverersGameMode();

	FORCEINLINE UBaseController* GetBaseController() { return BaseController; }
	FORCEINLINE UEnemyController* GetEnemyController() { return EnemyController; }

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UBaseController* BaseController;

	UPROPERTY(EditDefaultsOnly)
	UEnemyController* EnemyController;
};



