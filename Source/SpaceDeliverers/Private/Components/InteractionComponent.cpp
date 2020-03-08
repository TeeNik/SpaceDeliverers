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

	UE_LOG(LogTemp, Log, TEXT("UInteractionComponent::OnFire: %d"), Interactive != NULL);
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
	GLog->Log("OnOverlapBegin");
	Interactive = interactive;
	Interactive->OnSelect(this);
}

void UInteractionComponent::OnDeselect()
{
	GLog->Log("OnDeselect");
	if (Interactive != NULL) {
		GLog->Log("OnOverlapEnd");
		Interactive->OnDeselect();
		Interactive = NULL;
	}
}
