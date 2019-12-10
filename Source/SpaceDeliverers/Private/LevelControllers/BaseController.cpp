#include "BaseController.h"
#include "UI/MainWidget.h"
#include "Engine/World.h"
#include "SpaceLevelScript.h"
#include "Shield.h"

UBaseController::UBaseController()
{
}


void UBaseController::BeginPlay()
{
	Super::BeginPlay();

	auto level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());


	GLog->Log("Here");
	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetBP);
	MainWidget->AddToViewport();
}

void UBaseController::OnShieldUpdate(float value)
{
	MainWidget->UpdateShield(value);
}
