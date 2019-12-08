#include "SpaceDeliverersGameMode.h"
#include "SpaceDeliverersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseController.h"

ASpaceDeliverersGameMode::ASpaceDeliverersGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	BaseController = CreateDefaultSubobject<UBaseController>(TEXT("BaseController"));
}
