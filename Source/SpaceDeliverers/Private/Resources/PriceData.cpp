#include "PriceData.h"
#include "Gem.h"

PriceData::PriceData(GemType type, int value)
{
	Type = type;
	Value = value;
}

PriceData::~PriceData()
{
}

