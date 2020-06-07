#include "PriceItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Engine/Texture2D.h"

#include "PriceData.h"
#include "Gem.h"

void UPriceItem::Init(UPriceData* data)
{
	switch (data->Type) {
	case GemType::Blue:
		Icon->SetBrushFromTexture(BlueIcon);
		break;
	case GemType::Green:
		Icon->SetBrushFromTexture(GreenIcon);
		break;
	case GemType::Purple:
		Icon->SetBrushFromTexture(PurpleIcon);
		break;
	}
	Text->SetText(FText::FromString(FString::FromInt(data->Value)));
}

