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

	MainWidget = CreateWidget<UMainWidget>(GetWorld(), MainWidgetBP);
	MainWidget->AddToViewport();
}

void UBaseController::TakeDamage(const int & damage)
{
	Health -= damage;
	if (Health <= 0) {
		//Game over
	}
}

void UBaseController::BeginPlay()
{
	Super::BeginPlay();

}

void UBaseController::OnShieldUpdate(float value)
{
	MainWidget->UpdateShield(value);
}
