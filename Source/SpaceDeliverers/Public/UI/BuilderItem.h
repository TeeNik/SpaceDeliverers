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

UCLASS()
class SPACEDELIVERERS_API UBuilderItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(FBuildingData* data, FBuildingSelected onBuildingSelected);

protected:
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* PriceBox;

	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UPriceItem> PriceItemBP;

	UPROPERTY(meta = (BindWidget))
	UButton* ClickButton;

	UFUNCTION()
	void OnClick();

private:
	FBuildingData* Data;
	FBuildingSelected OnBuildingSelected;
};
