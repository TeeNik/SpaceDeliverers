#include "EnemyBot.h"
#include "Instrument.h"
#include "Gun.h"
#include "InteractionComponent.h"
#include "Utils/TagStrings.h"
#include "BuildingPlatform.h"

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

void AEnemyBot::OnSpawn(ABuildingPlatform* targetPlatform)
{
	Target = targetPlatform;
}

void AEnemyBot::OnDestroyReached()
{
	UE_LOG(LogTemp, Log, TEXT("AEnemyBot::OnDestroyReached"));
}

void AEnemyBot::OnCrashReached()
{
	UE_LOG(LogTemp, Log, TEXT("AEnemyBot::OnCrashReached"));
}

void AEnemyBot::OnSelect(UInteractionComponent* interComp)
{
	GetMesh()->SetRenderCustomDepth(true);
}

void AEnemyBot::OnDeselect()
{
	GetMesh()->SetRenderCustomDepth(false);
}