#include "Toolbox.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Wrench.h"
#include "InteractionComponent.h"

AToolbox::AToolbox()
{
}

void AToolbox::Interact(class UInteractionComponent* interComp, ACharacter* character)
{
	if (interComp->GetInstrument() == NULL) {
		AInstrument* wrench = GetWorld()->SpawnActor<AInstrument>(WrenchBase);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
		wrench->AttachToComponent(character->GetMesh(), rules, FName("InstrumentSocket"));
		interComp->SetInstrument(wrench);
	}
}

void AToolbox::BeginPlay()
{
	Super::BeginPlay();
}


