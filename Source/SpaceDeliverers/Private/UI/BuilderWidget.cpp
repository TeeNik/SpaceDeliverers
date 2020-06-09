#include "BuilderWidget.h"
#include "Engine/World.h"
#include "Button.h"
#include "ResourceManagerSingleton.h"
#include "ResourceManagerLibrary.h"
#include "Engine/DataTable.h"
#include "BuildingData.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "BuilderItem.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/HorizontalBox.h"

void UBuilderWidget::Init(FBuildingSelected& onBuildingSelected) 
{
	OnBuildingSelected = onBuildingSelected;
	CloseButton->OnClicked.AddDynamic(this, &UBuilderWidget::CloseWidget);

	UDataTable* dataTable = UResourceManagerLibrary::GetData()->BuildingDataTable;
	TArray<FBuildingData*> buildingDatas;
	dataTable->GetAllRows(TEXT(""), buildingDatas);

	UE_LOG(LogTemp, Log, TEXT("UBuilderWidget::Init"));
	for (auto data : buildingDatas) {
		UE_LOG(LogTemp, Log, TEXT("auto data : buildingDatas"));
		UBuilderItem* builderItem = WidgetTree->ConstructWidget<UBuilderItem>(BuilderItemBP);
		ItemsContainer->AddChildToHorizontalBox(builderItem);
		OnBuildingSelected.AddDynamic(this, &UBuilderWidget::OnSelected);
		builderItem->Init(data, OnBuildingSelected);
	}
}

void UBuilderWidget::OnSelected(TSubclassOf<AActor> actor)
{
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
