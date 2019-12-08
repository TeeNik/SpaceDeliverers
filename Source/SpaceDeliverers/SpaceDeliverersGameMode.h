#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SpaceDeliverersGameMode.generated.h"

class UBaseController;

UCLASS(minimalapi)
class ASpaceDeliverersGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASpaceDeliverersGameMode();

	FORCEINLINE UBaseController* GetBaseController() { return BaseController; }

private:
	UPROPERTY(EditDefaultsOnly)
	UBaseController* BaseController;
};



