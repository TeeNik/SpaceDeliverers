#include "BuilderItem.h"
#include "BuildingData.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/HorizontalBox.h"

#include "PriceData.h"
#include "PriceItem.h"
#include "Gem.h"

void UBuilderItem::Init(const FBuildingData* data)
{
	Data = data;

	for (auto price : Data->Prices) {
		if (price->Value != 0) {
			UPriceItem* priceItem = WidgetTree->ConstructWidget<UPriceItem>(PriceItemBP);
			priceItem->Init(price);
			PriceBox->AddChildToHorizontalBox(priceItem);
		}
	}
}

