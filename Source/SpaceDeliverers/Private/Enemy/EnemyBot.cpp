#include "EnemyBot.h"
#include "Instrument.h"
#include "Gun.h"
#include "InteractionComponent.h"
#include "Utils/TagStrings.h"

AEnemyBot::AEnemyBot()
{
	Tags.Add(TagStrings::EnemyTag);
}

void AEnemyBot::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AEnemyBot::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Gun) {
		const AGun* gun = Cast<AGun>(inHand);
		float damage = gun->GetDamage();
		gun->Shoot(this);
		OnBotHit(character, InteractionTime);
		return true;
	}
	return false;
}

void AEnemyBot::OnSelect(UInteractionComponent* interComp)
{
	GetMesh()->SetRenderCustomDepth(true);
}

void AEnemyBot::OnDeselect()
{
	GetMesh()->SetRenderCustomDepth(false);
}