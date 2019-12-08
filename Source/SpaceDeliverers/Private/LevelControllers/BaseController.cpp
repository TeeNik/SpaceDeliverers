#include "BaseController.h"
#include "UI/MainWidget.h"
#include "Engine/World.h"


UBaseController::UBaseController()
{
}


void UBaseController::BeginPlay()
{
	Super::BeginPlay();

	GLog->Log("Here");
	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetBP);
	MainWidget->AddToViewport();
}
