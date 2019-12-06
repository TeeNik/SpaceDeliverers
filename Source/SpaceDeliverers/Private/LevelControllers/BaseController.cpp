#include "BaseController.h"
#include "UI/MainWidget.h"
#include "Engine/World.h"


UBaseController::UBaseController()
{
}


void UBaseController::BeginPlay()
{
	Super::BeginPlay();

	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetBP);
}
