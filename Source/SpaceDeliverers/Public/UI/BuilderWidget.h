#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "BuildingBot.h"

#include "BuilderWidget.generated.h"

class UButton;
class UBuilderItem;
class UHorizontalBox;
struct FBuildingData;

UCLASS()
class SPACEDELIVERERS_API UBuilderWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(FBuildingSelected& onBuildingSelected);

	void ShowWidget();

protected:
	UPROPERTY(meta = (BindWidget))
	UButton* CloseButton;

	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* ItemsContainer;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBuilderItem> BuilderItemBP;

private:
	FBuildingSelected OnBuildingSelected;
	
	UFUNCTION()
	void OnSelected(FBuildingData& data);

	UFUNCTION()
	void CloseWidget();

	UPROPERTY()
	TArray<UBuilderItem*> BuilderItems;

	void CheckBuilderItemsPrices(const TArray<int>& gems);
};
