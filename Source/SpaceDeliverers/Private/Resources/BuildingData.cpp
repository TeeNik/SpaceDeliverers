#include "Resources/BuildingData.h"
#include "Gem.h"
#include "Engine/World.h"
#include "PriceData.h"

TArray<UPriceData*>& FBuildingData::GetPrices()
{
	if (Prices.Num() == 0) {
		auto greenPrice = NewObject<UPriceData>();
		greenPrice->SetData(GemType::Green, GreenGems);

		auto bluePrice = NewObject<UPriceData>();
		bluePrice->SetData(GemType::Blue, BlueGems);

		auto purplePrice = NewObject<UPriceData>();
		purplePrice->SetData(GemType::Purple, PurpleGems);

		Prices.Add(greenPrice);
		Prices.Add(purplePrice);
		Prices.Add(bluePrice);
	}
	return Prices;
}
