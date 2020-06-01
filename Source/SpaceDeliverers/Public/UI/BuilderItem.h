#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuilderItem.generated.h"

class UHorizontalBox;
class UImage;
struct FBuildingData;

UCLASS()
class SPACEDELIVERERS_API UBuilderItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(const FBuildingData* data);

protected:
	
	UPROPERTY(meta = (BindWidget))
	UHorizontalBox* PriceBox;

	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

private:
	const FBuildingData* Data;
	
};
