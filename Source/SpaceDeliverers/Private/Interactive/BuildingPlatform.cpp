#include "BuildingPlatform.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Builder.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

void ABuildingPlatform::OnSelect(UInteractionComponent * interComp) {
	auto instrument = interComp->GetInstrument();
	if (instrument != nullptr && instrument->GetType() == InstrumentType::Builder && previewActor == nullptr) {
		Super::OnSelect(interComp);
		GLog->Log("Builder instrument");

		const ABuilder* builder = Cast<ABuilder>(instrument);
		auto spawningActor = builder->GetSpawningActor();
		
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		previewActor = GetWorld()->SpawnActor<AActor>(spawningActor, GetActorLocation(), GetActorRotation(), ActorSpawnParams);

		previewActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		previewActor->SetActorRelativeLocation(SpawnPoint);

		auto mesh = Cast<UStaticMeshComponent>(previewActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		auto numOfMaterials = mesh->GetNumMaterials();
		for (size_t i = 0; i < numOfMaterials; ++i)
		{
			mesh->SetMaterial(i, PreviewMaterial);
		}
	}
}

void ABuildingPlatform::OnDeselect()
{
	Super::OnDeselect();
	if (previewActor != nullptr) {
		previewActor->Destroy();
		previewActor = nullptr;
	}
}
