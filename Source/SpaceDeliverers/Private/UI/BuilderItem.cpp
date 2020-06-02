#include "BuilderItem.h"
#include "BuildingData.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "Runtime/UMG/Public/Components/Spacer.h"
#include "Components/HorizontalBoxSlot.h"

void UBuilderItem::Init(const FBuildingData* data)
{
	Data = data;

	USpacer* spacer1 = WidgetTree->ConstructWidget<USpacer>(USpacer::StaticClass());

	if (Data->BlueGems) {

	}

}

