#include "BuilderItem.h"
#include "BuildingData.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/HorizontalBox.h"

#include "PriceData.h"
#include "PriceItem.h"
#include "Gem.h"

void UBuilderItem::Init(FBuildingData* data)
{
	Data = data;
	UE_LOG(LogTemp, Log, TEXT("UBuilderItem::Init"));
	auto prices = Data->GetPrices();
	UE_LOG(LogTemp, Log, TEXT("Data->Prices = %d"), prices.Num());
	for (auto price : prices) {
		if (!IsValid(price)) {
			UE_LOG(LogTemp, Log, TEXT("!IsValid(price)"));
			return;
		}
		UE_LOG(LogTemp, Log, TEXT("price->Value = %d"), price->Value);
		if (price->Value != 0) {
			UE_LOG(LogTemp, Log, TEXT("Init price: %d"), price->Value);
			UPriceItem* priceItem = WidgetTree->ConstructWidget<UPriceItem>(PriceItemBP);
			priceItem->Init(price);
			PriceBox->AddChildToHorizontalBox(priceItem);
		}
	}
}

