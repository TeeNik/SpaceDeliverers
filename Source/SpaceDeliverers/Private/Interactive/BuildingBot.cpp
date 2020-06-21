#include "BuildingBot.h"
#include "InteractionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Builder.h"
#include "BuilderWidget.h"
#include "AIController.h"
#include "SpaceLevelScript.h"
#include "BuildingPlatform.h"

ABuildingBot::ABuildingBot()
{
	OnBuildingSelected.AddDynamic(this, &ABuildingBot::BuildingSelected);
}

void ABuildingBot::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(BuilderWidgetBP)) {
		BuilderWidget = CreateWidget<UBuilderWidget>(GetWorld(), BuilderWidgetBP);
		BuilderWidget->AddToViewport();
		BuilderWidget->SetVisibility(ESlateVisibility::Hidden);
		BuilderWidget->Init(OnBuildingSelected);
	}

	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	Home = level->GetBuildingBotHome();
}

void ABuildingBot::OnReturnToHome()
{
	IsBusy = false;
}

void ABuildingBot::BuildingSelected(TSubclassOf<AActor> spawnActor)
{
	ABuilder* builder = GetWorld()->SpawnActor<ABuilder>(BuilderBase);
	FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
	ACharacter* character = Cast<ACharacter>(InteractionComponent->GetOwner());
	if (IsValid(character)) {
		builder->SetSpawnActor(spawnActor);
		builder->AttachToComponent(character->GetMesh(), rules, FName("BuilderSocket"));
		InteractionComponent->SetInstrument(builder);
	}
}

bool ABuildingBot::Interact(UInteractionComponent * interComp, ACharacter * character)
{
	if (interComp->GetInstrument() == NULL && !IsBusy) {
		BuilderWidget->ShowWidget();
		InteractionComponent = interComp;
		return true;
	}
	return false;
}

void ABuildingBot::OnSelect(UInteractionComponent * interComp)
{
	GetMesh()->SetRenderCustomDepth(true);
}

void ABuildingBot::OnDeselect()
{
	GetMesh()->SetRenderCustomDepth(false);
}

void ABuildingBot::Build(ABuildingPlatform* dest, const float duration)
{
	IsBusy = true;
	OnBuildBP(dest, duration);
}
