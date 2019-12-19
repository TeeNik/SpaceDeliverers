#include "ArmoryBox.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Gun.h"

AArmoryBox::AArmoryBox()
{
}

void AArmoryBox::Interact(AInstrument *& inHand, ACharacter * character)
{
	if (inHand == NULL) {
		inHand = GetWorld()->SpawnActor<AGun>(GunBase);
		FAttachmentTransformRules rules(EAttachmentRule::SnapToTarget, false);
		inHand->AttachToComponent(character->GetMesh(), rules, FName("WeaponSocket"));
	}
}

void AArmoryBox::BeginPlay()
{
	Super::BeginPlay();
}