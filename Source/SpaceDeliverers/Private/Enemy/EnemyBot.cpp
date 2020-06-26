#include "EnemyBot.h"
#include "Instrument.h"
#include "Gun.h"
#include "InteractionComponent.h"
#include "Utils/TagStrings.h"
#include "Components/WidgetComponent.h"
#include "Destructible.h"
#include "Kismet/GameplayStatics.h"
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
		if (TargetPlatform != nullptr) {
			TargetPlatform->IsBotTarget = false;
		}
		WidgetComponent->SetVisibility(false);
		IsDestroying = true;
		const AGun* gun = Cast<AGun>(inHand);
		gun->Shoot(this);
		OnBotHit(character, InteractionTime);
		if (Target != nullptr) {
			Target->TargetRelease();
		}
		return true;
	}
	return false;
}


void AEnemyBot::SetTargetPlatform(ABuildingPlatform* platform)
{
	TargetPlatform = platform;
	TargetPlatform->IsBotTarget = true;
	OnFoundTarget(platform->GetPlacedActor());
}

void AEnemyBot::OnTargetReached()
{
	Target = Cast<IDestructible>(TargetPlatform->GetPlacedActor());
}

void AEnemyBot::OnCrashReached()
{
	Target->CrashReached();
}

void AEnemyBot::OnDestroyReached()
{
	TargetPlatform->DestroyByBot();
	TargetPlatform = nullptr;
	Target->DestroyReached();
	Target = nullptr;
}

void AEnemyBot::OnDestroy()
{
	OnDeathCallback.Broadcast();
	if (ExplosionParticle != NULL) {
		auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ExplosionParticle, GetActorLocation());
		particle->SetWorldScale3D(ParticleSize);
	}
	Destroy();
}

void AEnemyBot::OnSelect(UInteractionComponent* interComp)
{
	GetMesh()->SetRenderCustomDepth(true);
}

void AEnemyBot::OnDeselect()
{
	GetMesh()->SetRenderCustomDepth(false);
}