#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BuilderItem.generated.h"

class UHorizontalBox;
class UImage;
struct FBuildingData;
class UTexture2D;

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

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* BlueGemIcon;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* PurpleGemIcon;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* GreenGemIcon;

private:
	const FBuildingData* Data;
	
};
