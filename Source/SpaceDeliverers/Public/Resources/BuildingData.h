#pragma once
#include "Engine/DataTable.h"
#include "BuildingData.generated.h"

class UTexture2D;
class UPriceData;

/*class SimpleData {
public:
	int value;
};*/

USTRUCT(BlueprintType)
struct SPACEDELIVERERS_API FBuildingData : public FTableRowBase
{
	GENERATED_BODY()

public:
	FBuildingData();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	int Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	TSubclassOf<AActor> ActorToBuild;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	float BuildingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Building Data")
	UTexture2D* Icon;

	//TArray<UPriceData> Prices;
};
