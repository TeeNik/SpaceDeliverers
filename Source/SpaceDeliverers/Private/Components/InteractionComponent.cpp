#include "InteractionComponent.h"
#include "Instruments/Instrument.h"
#include "Interactive.h"
#include "GameFramework/Character.h"
#include "BaseController.h"
#include "SpaceDeliverersGameMode.h"
#include "MainWidget.h"

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
		float time = Interactive->GetInteractionTime();
		if (Interactive->Interact(this, Cast<ACharacter>(GetOwner()))) {
			if (time > 0) {
				auto* GM = Cast<ASpaceDeliverersGameMode>(GetWorld()->GetAuthGameMode());
				if (IsValid(GM)) {
					GM->GetBaseController()->GetMainWidget()->ShowActionProgress(time);
				}
				//Show Interaction ()
			}
			
		}
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
	Interactive = interactive;
	Interactive->OnSelect(this);
}

void UInteractionComponent::OnDeselect()
{
	if (Interactive != NULL) {
		Interactive->OnDeselect();
		Interactive = NULL;
	}
}
