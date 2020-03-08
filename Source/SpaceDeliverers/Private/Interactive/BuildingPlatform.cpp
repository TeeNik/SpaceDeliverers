#include "BuildingPlatform.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Builder.h"
#include "Engine/World.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInterface.h"

ABuildingPlatform::ABuildingPlatform() {
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPoint->SetupAttachment(Mesh);
}

void ABuildingPlatform::OnSelect(UInteractionComponent * interComp) {
	auto instrument = interComp->GetInstrument();
	if (instrument != nullptr && instrument->GetType() == InstrumentType::Builder && PreviewActor == nullptr && PlacedActor == nullptr) {
		Super::OnSelect(interComp);

		const ABuilder* builder = Cast<ABuilder>(instrument);
		auto spawningActor = builder->GetSpawningActor();
		
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PreviewActor = GetWorld()->SpawnActor<AActor>(spawningActor, GetActorLocation(), GetActorRotation(), ActorSpawnParams);

		PreviewActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		PreviewActor->SetActorLocation(SpawnPoint->GetComponentLocation());

		auto mesh = Cast<UStaticMeshComponent>(PreviewActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
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
	if (PreviewActor != nullptr) {
		PreviewActor->Destroy();
		PreviewActor = nullptr;
	}
}

bool ABuildingPlatform::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	auto instrument = interComp->GetInstrument();
	UE_LOG(LogTemp, Log, TEXT("ABuildingPlatform::Interact: %d %d"), PreviewActor != nullptr, PlacedActor == nullptr);
	if (instrument != nullptr && instrument->GetType() == InstrumentType::Builder && PreviewActor != nullptr && PlacedActor == nullptr) {
		const ABuilder* builder = Cast<ABuilder>(instrument);
		auto spawningActor = builder->GetSpawningActor();

		PreviewActor->Destroy();
		PreviewActor = nullptr;

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		PlacedActor = GetWorld()->SpawnActor<AActor>(spawningActor, GetActorLocation(), GetActorRotation(), ActorSpawnParams);

		PlacedActor->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
		PlacedActor->SetActorLocation(SpawnPoint->GetComponentLocation());
		return true;
	}
	return false;
}
