#include "BuilderWidget.h"
#include "Engine/World.h"
#include "Button.h"

void UBuilderWidget::Init(FBuildingSelected& onBuildingSelected) 
{
	OnBuildingSelected = onBuildingSelected;
	TurretButton->OnClicked.AddDynamic(this, &UBuilderWidget::OnTurretButtonClicked);
	CloseButton->OnClicked.AddDynamic(this, &UBuilderWidget::CloseWidget);
}

void UBuilderWidget::OnTurretButtonClicked()
{
	UE_LOG(LogTemp, Log, TEXT("UBuilderWidget::OnTurretButtonClicked"));
	OnBuildingSelected.Broadcast();
	CloseWidget();
}

void UBuilderWidget::ShowWidget()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	if (IsValid(pc)) {
		FInputModeUIOnly mode;
		mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		pc->SetInputMode(mode);
		pc->bShowMouseCursor = true;
		SetVisibility(ESlateVisibility::Visible);
	}
}

void UBuilderWidget::CloseWidget()
{
	auto pc = GetWorld()->GetFirstPlayerController();
	if (IsValid(pc)) {
		pc->bShowMouseCursor = false;
		FInputModeGameOnly mode;
		pc->SetInputMode(mode);
		SetVisibility(ESlateVisibility::Hidden);
	}
}
