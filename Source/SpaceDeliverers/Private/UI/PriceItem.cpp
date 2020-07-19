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
		Icon->SetColorAndOpacity(Blue);
		break;
	case GemType::Green:
		Icon->SetBrushFromTexture(GreenIcon);
		Icon->SetColorAndOpacity(Green);
		break;
	case GemType::Purple:
		Icon->SetBrushFromTexture(PurpleIcon);
		Icon->SetColorAndOpacity(Purple);
		break;
	}
	Text->SetText(FText::FromString(FString::FromInt(data->Value)));
}

