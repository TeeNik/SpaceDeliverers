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
#include "Components/Spacer.h"

void UBuilderWidget::Init(FBuildingSelected& onBuildingSelected) 
{
	OnBuildingSelected = onBuildingSelected;
	CloseButton->OnClicked.AddDynamic(this, &UBuilderWidget::CloseWidget);
	OnBuildingSelected.AddDynamic(this, &UBuilderWidget::OnSelected);

	UDataTable* dataTable = UResourceManagerLibrary::GetData()->BuildingDataTable;
	TArray<FBuildingData*> buildingDatas;
	dataTable->GetAllRows(TEXT(""), buildingDatas);
	const FSlateChildSize size(ESlateSizeRule::Fill);

	for (int i = 0; i < buildingDatas.Num(); ++i) {
		UBuilderItem* builderItem = WidgetTree->ConstructWidget<UBuilderItem>(BuilderItemBP);
		ItemsContainer->AddChildToHorizontalBox(builderItem);
		builderItem->Init(buildingDatas[i], OnBuildingSelected);
		if (i != buildingDatas.Num() - 1) {
			USpacer* spacer = WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());
			UHorizontalBoxSlot* spacelSlot = ItemsContainer->AddChildToHorizontalBox(spacer);
			spacelSlot->SetSize(size);
		}
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
	UE_LOG(LogTemp, Log, TEXT("UBuilderWidget::CloseWidget"));
	auto pc = GetWorld()->GetFirstPlayerController();
	if (IsValid(pc)) {
		pc->bShowMouseCursor = false;
		FInputModeGameOnly mode;
		pc->SetInputMode(mode);
		SetVisibility(ESlateVisibility::Hidden);
	}
}
