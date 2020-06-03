#pragma once

#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
//#include "PriceData.generated.h"

enum GemType;

//UCLASS()
class SPACEDELIVERERS_API PriceData
{
public:
	PriceData() {};
	PriceData(GemType type, int value);
	~PriceData();

	int Value;
	GemType Type;
};
