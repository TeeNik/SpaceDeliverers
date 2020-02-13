#include "BuildingBot.h"
#include "InteractionComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Builder.h"

ABuildingBot::ABuildingBot() {
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Mesh->SetupAttachment(Box);
}

bool ABuildingBot::Interact(UInteractionComponent * interComp, ACharacter * character)
{
	if (interComp->GetInstrument() == NULL) {
		ABuilder* builder = GetWorld()->SpawnActor<ABuilder>(BuilderBase);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
		builder->AttachToComponent(character->GetMesh(), rules, FName("InstrumentSocket"));
		builder->SetActorRelativeScale3D(FVector(.2f, .2f, .2f));
		interComp->SetInstrument(builder);
		return true;
	}
	return false;
}

void ABuildingBot::OnSelect(UInteractionComponent * interComp)
{
	GLog->Log("on select");
	Mesh->SetRenderCustomDepth(true);
}

void ABuildingBot::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
}
