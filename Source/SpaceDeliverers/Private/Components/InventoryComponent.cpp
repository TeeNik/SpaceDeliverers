#include "InventoryComponent.h"
#include "InventoryWidget.h"
#include "Gem.h"


UInventoryComponent::UInventoryComponent()
{

}

void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	Gems.SetNum(3);

	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld(), InventoryWidgetBP);
	InventoryWidget->AddToViewport();
	InventoryWidget->Init();
}


void UInventoryComponent::CollectCrystal(GemType type)
{
	if (type < Gems.Num()) {
		++Gems[type];
		InventoryWidget->SetGemValue(type, Gems[type]);
	}
}
