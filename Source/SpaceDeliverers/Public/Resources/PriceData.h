#pragma once

#include "Engine/DataTable.h"
#include "PriceData.generated.h"


USTRUCT()
struct SPACEDELIVERERS_API FPriceData : public FTableRowBase
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PriceData")
	int Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PriceData")
	int BlueGems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PriceData")
	int PurpleGems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PriceData")
	int GreenGems;
	
};
