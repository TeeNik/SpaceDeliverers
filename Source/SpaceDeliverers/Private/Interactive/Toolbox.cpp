#include "Toolbox.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Wrench.h"

AToolbox::AToolbox()
{
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void AToolbox::Interact(AInstrument*& inHand, const ACharacter* character)
{
	if (inHand == NULL) {
		inHand = GetWorld()->SpawnActor<AInstrument>(WrenchBase);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
		inHand->AttachToComponent(character->GetMesh(), rules, FName("InstrumentSocket"));
	}
}

void AToolbox::BeginPlay()
{
	Super::BeginPlay();
	
}


