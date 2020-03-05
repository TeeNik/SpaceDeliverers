#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

class UTextBlock;
enum GemType;

UCLASS()
class SPACEDELIVERERS_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void Init();
	void SetGemValue(GemType type, int value);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* BlueGems;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PurpleGems;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* GreenGems;

private:
	void SetBlueGems(int value);
	void SetGreenGems(int value);
	void SetPurpleGems(int value);
};
