#include "Resources/BuildingData.h"
#include "Gem.h"
#include "Engine/World.h"
#include "PriceData.h"

FBuildingData::FBuildingData()
{
	auto greenPrice = NewObject<UPriceData>();
	greenPrice->SetData(GemType::Green, GreenGems);

	auto bluePrice = NewObject<UPriceData>();
	bluePrice->SetData(GemType::Blue, GreenGems);

	auto purplePrice = NewObject<UPriceData>();
	purplePrice->SetData(GemType::Purple, GreenGems);

	Prices.Add(greenPrice);
	Prices.Add(purplePrice);
	Prices.Add(bluePrice);
}