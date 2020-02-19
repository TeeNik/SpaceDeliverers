#include "BuildingPlatform.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Builder.h"
#include "Engine/World.h"

void ABuildingPlatform::OnSelect(UInteractionComponent * interComp) {
	auto instrument = interComp->GetInstrument();
	if (instrument != nullptr && instrument->GetType() == InstrumentType::Builder) {
		Super::OnSelect(interComp);
		GLog->Log("Builder instrument");

		const ABuilder* builder = Cast<ABuilder>(instrument);
		auto spawningActor = builder->GetSpawningActor();
		
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		previewActor = GetWorld()->SpawnActor<AActor>(spawningActor, GetActorLocation(), GetActorRotation(), ActorSpawnParams);

		previewActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		previewActor->SetActorRelativeLocation(SpawnPoint);
	}
}

void ABuildingPlatform::OnDeselect()
{
	Super::OnDeselect();
	if (previewActor != nullptr) {
		previewActor->Destroy();
	}
}
