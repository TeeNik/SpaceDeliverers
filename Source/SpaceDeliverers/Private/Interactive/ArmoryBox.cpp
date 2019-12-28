#include "ArmoryBox.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Gun.h"
#include "InteractionComponent.h"

AArmoryBox::AArmoryBox()
{
}

void AArmoryBox::Interact(UInteractionComponent* interComp, ACharacter * character)
{
	if (interComp->GetInstrument() == NULL) {
		AGun* gun = GetWorld()->SpawnActor<AGun>(GunBase);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
		gun->AttachToComponent(character->GetMesh(), rules, FName("WeaponSocket"));
		interComp->SetInstrument(gun);
	}
}

void AArmoryBox::BeginPlay()
{
	Super::BeginPlay();
}