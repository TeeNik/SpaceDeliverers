#include "PriceItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

void UPriceItem::Init(UTexture2D* texture, FString text)
{
	Icon->SetBrushFromTexture(texture);
	Text->SetText(FText::FromString(text));
}

