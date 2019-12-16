#include "SpaceDeliverersGameMode.h"
#include "SpaceDeliverersCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BaseController.h"
#include "EnemyController.h"
#include "SpaceLevelScript.h"
#include "Shield.h"

ASpaceDeliverersGameMode::ASpaceDeliverersGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	BaseController = CreateDefaultSubobject<UBaseController>(TEXT("BaseController"));
	EnemyController = CreateDefaultSubobject<UEnemyController>(TEXT("EnemyController"));
}

void ASpaceDeliverersGameMode::BeginPlay()
{
	Super::BeginPlay();
	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	BaseController->Initialize();
	EnemyController->Initialize();
	level->GetShield()->Initialize();
}
