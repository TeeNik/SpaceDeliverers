#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuildingBot.h"
#include "BuilderItem.generated.h"

class UHorizontalBox;
class UImage;
struct FBuildingData;
class UTexture2D;
class UPriceItem;
class UButton;
class UPriceData;

UCLASS()
class SPACEDELIVERERS_API UBuilderItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(FBuildingData* data, FBuildingSelected& onBuildingSelected);
	void CheckPrices(const TArray<int>& gems);

protected:
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* PriceBox;

	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	UImage* Shadow;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPriceItem> PriceItemBP;

	UPROPERTY(meta = (BindWidget))
	UButton* ClickButton;

	UFUNCTION()
	void OnClick();

private:
	UPROPERTY()
	TArray<UPriceData*> Prices;

	FBuildingData* Data;
	FBuildingSelected OnBuildingSelected;
};
