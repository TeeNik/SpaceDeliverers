#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PriceItem.generated.h"

class UTextBlock;
class UImage;
class UTexture2D;
class UPriceData;

UCLASS()
class SPACEDELIVERERS_API UPriceItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UPriceData* data);

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* GreenIcon;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* BlueIcon;

	UPROPERTY(EditDefaultsOnly)
	UTexture2D* PurpleIcon;
	
	UPROPERTY(EditDefaultsOnly)
	FLinearColor Green;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor Blue;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor Purple;
};
