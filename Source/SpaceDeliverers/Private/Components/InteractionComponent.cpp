#include "InteractionComponent.h"
#include "Instruments/Instrument.h"
#include "Interactive.h"
#include "GameFramework/Character.h"

UInteractionComponent::UInteractionComponent()
{
}

void UInteractionComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UInteractionComponent::OnFire()
{
	if (Instrument != NULL) {
		Instrument->Use();
	}

	if (Interactive != NULL) {
		Interactive->Interact(Instrument, Cast<ACharacter>(GetOwner()));
	}
}

void UInteractionComponent::OnRelease()
{
	if (Instrument != NULL) {
		Instrument->Release();
		Instrument = NULL;
	}
}

void UInteractionComponent::OnSelect(IInteractive * interactive)
{
	GLog->Log("OnOverlapBegin");
	Interactive = interactive;
	Interactive->OnSelect();
}

void UInteractionComponent::OnDeselect()
{
	if (Interactive != NULL) {
		GLog->Log("OnOverlapEnd");
		Interactive->OnDeselect();
		Interactive = NULL;
	}
}
