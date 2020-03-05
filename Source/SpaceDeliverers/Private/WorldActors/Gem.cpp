#include "Gem.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InventoryComponent.h"
#include "SpaceDeliverersCharacter.h"
#include "Utils/TagStrings.h"

AGem::AGem()
{
	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	RootComponent = Sphere;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Sphere);
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AGem::OnOverlapBegin);
}

void AGem::PlaySpawnAnimation(FVector spawnLocation)
{
	float angle = FMath::RandRange(0, 360);
	float x = FMath::Cos(angle) * Radius;
	float y = FMath::Sin(angle) * Radius;

	OnPlaySpawnAnimation(spawnLocation, x, y);
}

void AGem::BeginPlay()
{
	Super::BeginPlay();
}

void AGem::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag(TagStrings::PlayerTag)) {
		ASpaceDeliverersCharacter* character = Cast<ASpaceDeliverersCharacter>(OtherActor);
		if (IsValid(character)) {
			character->GetInventoryComponent()->CollectCrystal(Type);
			OnCollect();
		}
	}
	
}
