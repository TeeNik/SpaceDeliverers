#include "BuildingBot.h"
#include "InteractionComponent.h"
#include "GameFramework/Character.h"
#include "Builder.h"

ABuildingBot::ABuildingBot() {

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
