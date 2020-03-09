#include "BuildingBot.h"
#include "InteractionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Builder.h"
#include "BuilderWidget.h"

ABuildingBot::ABuildingBot()
{
}

void ABuildingBot::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BuilderWidgetBP)) {
		BuilderWidget = CreateWidget<UBuilderWidget>(GetWorld(), BuilderWidgetBP);
		BuilderWidget->AddToViewport();
		BuilderWidget->SetVisibility(ESlateVisibility::Hidden);
		BuilderWidget->Init(OnBuildingSelected);
		OnBuildingSelected.AddDynamic(this, &ABuildingBot::BuildingSelected);
	}
}

void ABuildingBot::BuildingSelected()
{
	ABuilder* builder = GetWorld()->SpawnActor<ABuilder>(BuilderBase);
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
	ACharacter* character = Cast<ACharacter>(InteractionComponent->GetOwner());
	if (IsValid(character)) {
		builder->AttachToComponent(character->GetMesh(), rules, FName("InstrumentSocket"));
		builder->SetActorRelativeScale3D(FVector(.2f, .2f, .2f));
		InteractionComponent->SetInstrument(builder);
	}
}

bool ABuildingBot::Interact(UInteractionComponent * interComp, ACharacter * character)
{
	if (interComp->GetInstrument() == NULL) {
		BuilderWidget->ShowWidget();
		InteractionComponent = interComp;
		return true;
	}
	return false;
}

void ABuildingBot::OnSelect(UInteractionComponent * interComp)
{
	GLog->Log("on select");
	GetMesh()->SetRenderCustomDepth(true);
}

void ABuildingBot::OnDeselect()
{
	GetMesh()->SetRenderCustomDepth(false);
}