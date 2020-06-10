#include "BuilderItem.h"
#include "BuildingData.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"

#include "PriceData.h"
#include "PriceItem.h"
#include "Gem.h"

void UBuilderItem::Init(FBuildingData* data, FBuildingSelected onBuildingSelected)
{
	Data = data;
	OnBuildingSelected = onBuildingSelected;
	auto prices = Data->GetPrices();
	for (auto price : prices) {
		if (price->Value != 0) {
			UPriceItem* priceItem = WidgetTree->ConstructWidget<UPriceItem>(PriceItemBP);
			priceItem->Init(price);
			PriceBox->AddChildToHorizontalBox(priceItem);
		}
	}
	ClickButton->OnClicked.AddDynamic(this, &UBuilderItem::OnClick);
}

void UBuilderItem::OnClick()
{
	OnBuildingSelected.Broadcast(Data->ActorToBuild);
}