#include "Toolbox.h"
#include "Instrument.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "InteractionComponent.h"

AToolbox::AToolbox()
{
}

bool AToolbox::Interact(class UInteractionComponent* interComp, ACharacter* character)
{
	if (interComp->GetInstrument() == NULL) {
		AInstrument* instrument = GetWorld()->SpawnActor<AInstrument>(InstrumentBase);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
		instrument->AttachToComponent(character->GetMesh(), rules, AttachSocket);
		//wrench->AttachToComponent(character->GetMesh(), rules, FName("InstrumentSocket"));
		interComp->SetInstrument(instrument);
		return true;
	}
	return false;
}