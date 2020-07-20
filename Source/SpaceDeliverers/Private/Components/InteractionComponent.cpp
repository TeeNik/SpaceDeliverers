#include "InteractionComponent.h"
#include "Instruments/Instrument.h"
#include "Interactive.h"
#include "BaseController.h"
#include "SpaceDeliverersGameMode.h"
#include "MainWidget.h"
#include "SpaceDeliverersCharacter.h"

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
	if (Interactive != NULL) {
		float time = Interactive->GetInteractionTime();
		auto* character = Cast<ASpaceDeliverersCharacter>(GetOwner());

		InstrumentType instrumentType = Instrument != nullptr ? Instrument->GetType() : InstrumentType::None;
		if (Interactive->Interact(this, character)) {
			OnInstrumentUsed.Broadcast((int)instrumentType);

			//if (time > 0) {
			//	character->DisableMovement(time);
			//	auto* GM = Cast<ASpaceDeliverersGameMode>(GetWorld()->GetAuthGameMode());
			//	if (IsValid(GM)) {
			//		GM->GetBaseController()->GetMainWidget()->ShowActionProgress(time);
			//	}
			//}
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
