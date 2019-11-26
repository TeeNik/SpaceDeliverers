#include "Turret.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/HealthComponent.h"
#include "WeaponProjectile.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Mesh->SetupAttachment(Box);
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetActorRotation();
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &ATurret::Fire);
	PlayerInputComponent->BindAction("RMB", IE_Pressed, this, &ATurret::Release);
}

void ATurret::OnSelect()
{
	Mesh->SetRenderCustomDepth(true);
}

void ATurret::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
}

void ATurret::Interact(AInstrument*& inHand, ACharacter* character)
{
	if (inHand == NULL) {
		GetWorld()->GetFirstPlayerController()->Possess(this);
		Mesh->SetRenderCustomDepth(false);
		character->SetActorHiddenInGame(true);
		ShootingPerson = character;
	}
}

void ATurret::Fire()
{
	UWorld* const World = GetWorld();
	if (World != NULL && ProjectileBase != NULL)
	{
		float seconds = World->GetTimeSeconds();
		if (LastFire + FireRate < seconds) {
			LastFire = seconds;
			const FRotator SpawnRotation = GetControlRotation();
			const FVector SpawnLocation = GetActorLocation();
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AWeaponProjectile* shot = World->SpawnActor<AWeaponProjectile>(ProjectileBase, SpawnLocation, SpawnRotation, ActorSpawnParams);
			shot->SetTargetTag(TargetTag);
		}
	}
}

void ATurret::Release()
{
	if (ShootingPerson != NULL) {
		ShootingPerson->SetActorHiddenInGame(false);
		GetWorld()->GetFirstPlayerController()->Possess(ShootingPerson);
		SetActorRotation(InitialRotation);
		ShootingPerson = NULL;
	}
}