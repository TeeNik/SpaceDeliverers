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

void UInteractionComponent::SetInstrument(AInstrument * instrument)
{
	Instrument = instrument;
	if (instrument == NULL) {
		OnInstrumentChanged.Broadcast(InstrumentType::None);
	}
	else {
		OnInstrumentChanged.Broadcast(instrument->GetType());
	}
}

void UInteractionComponent::OnFire()
{
	if (Instrument != NULL) {
		Instrument->Use();
	}

	if (Interactive != NULL) {
		Interactive->Interact(this, Cast<ACharacter>(GetOwner()));
	}
}

void UInteractionComponent::OnRelease()
{
	if (Instrument != NULL) {
		Instrument->Release();
		SetInstrument(NULL);
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
