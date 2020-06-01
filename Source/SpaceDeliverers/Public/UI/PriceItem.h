#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PriceItem.generated.h"

class UTextBlock;
class UImage;
class UTexture2D;

UCLASS()
class SPACEDELIVERERS_API UPriceItem : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init(UTexture2D* texture, FString text);

protected:
	UPROPERTY(meta = (BindWidget))
	UImage* Icon;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Text;
	
};
