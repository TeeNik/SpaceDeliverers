#include "BaseController.h"
#include "UI/MainWidget.h"
#include "Engine/World.h"
#include "SpaceLevelScript.h"
#include "Shield.h"

UBaseController::UBaseController()
{
}


void UBaseController::Initialize()
{
	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	level->GetShield()->OnShieldUpdate.AddDynamic(this, &UBaseController::OnShieldUpdate);

	GLog->Log("Here");
	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetBP);
	MainWidget->AddToViewport();
}

void UBaseController::BeginPlay()
{
	Super::BeginPlay();

}

void UBaseController::OnShieldUpdate(float value)
{
	MainWidget->UpdateShield(value);
}
