#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Gem.h"
#include "SpaceLevelScript.h"
#include "BuildingBot.h"
#include "BuildingData.h"
#include "PriceData.h"

UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Gems.SetNum(3);

	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetBP);
	InventoryWidget->AddToViewport();
	InventoryWidget->Init();
}

void UInventoryComponent::SpendGems(FBuildingData& data)
{
	for (auto* price : data.GetPrices())
	{
		Gems[price->Type] -= price->Value;
	}
	UpdateUI();
}

void UInventoryComponent::UpdateUI()
{
	for (int i = 0; i < Gems.Num(); ++i)
	{
		InventoryWidget->SetGemValue((GemType)i, Gems[i]);
	}
}

void UInventoryComponent::CollectCrystal(GemType type)
{
	if (type < Gems.Num()) {
		++Gems[type];
		InventoryWidget->SetGemValue(type, Gems[type]);
	}
}
