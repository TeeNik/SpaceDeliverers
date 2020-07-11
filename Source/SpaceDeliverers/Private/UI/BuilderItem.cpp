#include "BuilderItem.h"
#include "BuildingData.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "PriceData.h"
#include "PriceItem.h"
#include "Gem.h"
#include "SpaceDeliverersCharacter.h"
#include "InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

void UBuilderItem::Init(FBuildingData* data, FBuildingSelected& onBuildingSelected)
{
	Data = data;
	Icon->SetBrushFromTexture(data->Icon);
	OnBuildingSelected = onBuildingSelected;
	Prices = Data->GetPrices();
	for (auto price : Prices) {
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
	auto* character = Cast<ASpaceDeliverersCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (IsValid(character)) {
		character->GetInventoryComponent()->SpendGems(*Data);
		OnBuildingSelected.Broadcast(*Data);
	}
}

void UBuilderItem::CheckPrices(const TArray<int>& gems)
{
	for (auto price : Prices)
	{
		if (gems[price->Type] < price->Value)
		{
			Shadow->SetVisibility(ESlateVisibility::Visible);
			return;
		}
	}
	Shadow->SetVisibility(ESlateVisibility::Hidden);
}
