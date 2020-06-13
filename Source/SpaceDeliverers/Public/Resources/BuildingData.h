#pragma once
#include "Engine/DataTable.h"
#include "BuildingData.generated.h"

class UTexture2D;
class UPriceData;
class UPriceItem;

USTRUCT(BlueprintType)
struct SPACEDELIVERERS_API FBuildingData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	TSubclassOf<AActor> ActorToBuild;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PriceData")
	int BlueGems;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PriceData")
	int PurpleGems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PriceData")
	int GreenGems;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	float BuildingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	UTexture2D* Icon;

	TArray<UPriceData*>& GetPrices();

private:

	bool IsInited;

	UPROPERTY(Transient)
	TArray<UPriceData*> Prices;
};
