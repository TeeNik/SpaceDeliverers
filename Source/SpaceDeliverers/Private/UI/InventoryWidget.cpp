#include "InventoryWidget.h"
#include "TextBlock.h"
#include "Gem.h"

void UInventoryWidget::Init()
{
	SetBlueGems(0);
	SetGreenGems(0);
	SetPurpleGems(0);
}

void UInventoryWidget::SetGemValue(GemType type, int value)
{
	switch (type) {
	case GemType::Purple:
		SetPurpleGems(value);
		break;
	case GemType::Blue:
		SetBlueGems(value);
		break;
	case GemType::Green:
		SetGreenGems(value);
		break;
	}
}

void UInventoryWidget::SetBlueGems(int value)
{
	BlueGems->SetText(FText::FromString(FString::FromInt(value)));
}

void UInventoryWidget::SetGreenGems(int value)
{
	GreenGems->SetText(FText::FromString(FString::FromInt(value)));
}

void UInventoryWidget::SetPurpleGems(int value)
{
	PurpleGems->SetText(FText::FromString(FString::FromInt(value)));
}
