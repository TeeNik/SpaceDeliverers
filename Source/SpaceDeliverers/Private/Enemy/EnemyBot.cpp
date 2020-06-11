#include "EnemyBot.h"
#include "Instrument.h"
#include "Gun.h"
#include "InteractionComponent.h"
#include "Utils/TagStrings.h"
#include "Components/WidgetComponent.h"
#include "Destructible.h"
#include "Particles/ParticleSystemComponent.h"
#include "BuildingPlatform.h"

AEnemyBot::AEnemyBot()
{
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComponent->SetupAttachment(RootComponent);
	SpawnParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SpawnParticle"));
	SpawnParticle->SetupAttachment(RootComponent);
	Tags.Add(TagStrings::EnemyBotTag);
}

void AEnemyBot::BeginPlay()
{
	Super::BeginPlay();
}

bool AEnemyBot::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	const AInstrument* inHand = interComp->GetInstrument();
	if (inHand != NULL && inHand->GetType() == InstrumentType::Gun) {
		TargetPlatform->IsBotTarget = false;
		WidgetComponent->SetVisibility(false);
		IsDestroying = true;
		const AGun* gun = Cast<AGun>(inHand);
		gun->Shoot(this);
		OnBotHit(character, InteractionTime);
		if (Target != nullptr) {
			Target->OnTargetRelease();
		}
		return true;
	}
	return false;
}

void AEnemyBot::OnTargetReached(AActor* destroyTarget)
{
	Target = Cast<IDestructible>(destroyTarget);
	if (Target != nullptr) {
		GLog->Log("Target is valid");
	}
}

void AEnemyBot::OnSelect(UInteractionComponent* interComp)
{
	GetMesh()->SetRenderCustomDepth(true);
}

void AEnemyBot::OnDeselect()
{
	GetMesh()->SetRenderCustomDepth(false);
}