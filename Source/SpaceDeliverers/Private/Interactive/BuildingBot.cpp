#include "BuildingBot.h"
#include "InteractionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Builder.h"
#include "BuilderWidget.h"
#include "AIController.h"
#include "SpaceLevelScript.h"

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
		UE_LOG(LogTemp, Log, TEXT("ABuildingBot::BeginPlay"));
	}

	ASpaceLevelScript* level = Cast<ASpaceLevelScript>(GetWorld()->GetLevelScriptActor());
	Home = level->GetBuildingBotHome();
}

void ABuildingBot::OnReturnToHome()
{
	IsBusy = false;
}

void ABuildingBot::BuildingSelected()
{
	UE_LOG(LogTemp, Log, TEXT("ABuildingBot::BuildingSelected"));
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

void ABuildingBot::Build(const AActor* dest, const float duration)
{
	UE_LOG(LogTemp, Log, TEXT("ABuildingBot::Build"));
	IsBusy = true;
	OnBuildBP(dest, duration);
}
