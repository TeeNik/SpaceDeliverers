#pragma once
#include "CoreMinimal.h"
#include "Gem.h"
#include "PriceData.generated.h"

UCLASS()
class SPACEDELIVERERS_API UPriceData : public UObject
{
	GENERATED_BODY()

public:
	void SetData(GemType type, int value);

	GemType Type;
	int Value;
	
};
