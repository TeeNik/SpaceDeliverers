#include "Turret.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/InputComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/PlayerController.h"
#include "WeaponProjectile.h"
#include "InteractionComponent.h"
#include "Camera/CameraShake.h"

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
	CurrentAmmo = MaxAmmo;
}

void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LMB", IE_Pressed, this, &ATurret::Fire);
	PlayerInputComponent->BindAction("RMB", IE_Pressed, this, &ATurret::Release);
}

bool ATurret::Interact(UInteractionComponent* interComp, ACharacter* character)
{
	if (!IsDestroying && interComp->GetInstrument() == NULL) {
		GetWorld()->GetFirstPlayerController()->Possess(this);
		Mesh->SetRenderCustomDepth(false);
		character->SetActorHiddenInGame(true);
		ShootingPerson = character;
		CharacterPos = ShootingPerson->GetActorLocation();
		ShootingPerson->SetActorLocation(FVector(10000, 10000, 10000));
	}
	return false;
}

void ATurret::OnSelect(UInteractionComponent * interComp)
{
	Mesh->SetRenderCustomDepth(true);
}

void ATurret::OnDeselect()
{
	Mesh->SetRenderCustomDepth(false);
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
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake, 1.0f);
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AWeaponProjectile* shot = World->SpawnActor<AWeaponProjectile>(ProjectileBase, SpawnLocation, SpawnRotation, ActorSpawnParams);
			shot->SetTargetTag(TargetTag);
			--CurrentAmmo;
			
			if (CurrentAmmo == 0) {
				IsDestroying = true;
				Release();
				OnAmmoEnd();
			}
		}
	}
}

void ATurret::Release()
{
	if (ShootingPerson != NULL) {
		ShootingPerson->SetActorHiddenInGame(false);
		GetWorld()->GetFirstPlayerController()->Possess(ShootingPerson);
		SetActorRotation(InitialRotation);
		ShootingPerson->SetActorLocation(CharacterPos);
		ShootingPerson = NULL;
	}
}