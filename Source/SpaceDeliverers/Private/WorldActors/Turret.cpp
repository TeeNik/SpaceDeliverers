#include "Turret.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/InputComponent.h"
#include "Components/HealthComponent.h"
#include "GameFramework/PlayerController.h"
#include "Camera/PlayerCameraManager.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Utils/TagStrings.h"

#include "WeaponProjectile.h"
#include "InteractionComponent.h"
#include "Instrument.h"
#include "Camera/CameraShake.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	SmokeParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SmokeParticle"));
	RootComponent = Arrow;
	Box->SetupAttachment(Arrow);
	Mesh->SetupAttachment(Arrow);
	SmokeParticle->SetupAttachment(Arrow);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Mesh);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
	SmokeParticle->SetVisibility(false);
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
	auto* instrument = interComp->GetInstrument();
	bool isCrashed = GetIsCrashed();
	if (!IsDestroying && instrument == nullptr && !GetIsTarget() && !isCrashed) {
		APlayerController* pc = GetWorld()->GetFirstPlayerController();
		pc->Possess(this);
		Mesh->SetRenderCustomDepth(false);
		character->SetActorHiddenInGame(true);
		ShootingPerson = character;
		CharacterPos = ShootingPerson->GetActorLocation();
		ShootingPerson->SetActorLocation(FVector(10000, 10000, 10000));

		APlayerCameraManager* cm = pc->PlayerCameraManager;
		UE_LOG(LogTemp, Log, TEXT("ViewYawMin: %d"), cm->ViewYawMin);
		UE_LOG(LogTemp, Log, TEXT("ViewYawMax: %d"), cm->ViewYawMax);
		UE_LOG(LogTemp, Log, TEXT("ViewPitchMin: %d"), cm->ViewPitchMin);
		UE_LOG(LogTemp, Log, TEXT("ViewPitchMax: %d"), cm->ViewPitchMax);

		pc->PlayerCameraManager->ViewYawMin = -180;
		pc->PlayerCameraManager->ViewYawMax = 0;
		pc->PlayerCameraManager->ViewPitchMin = 0;
		pc->PlayerCameraManager->ViewPitchMax = 40;
	}
	else if (!IsDestroying && isCrashed && instrument != nullptr && instrument->GetType() == InstrumentType::Wrench) {

		return true;
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

void ATurret::OnDestroyReached()
{
	IsDestroying = true;
	OnDestroy();
	UE_LOG(LogTemp, Log, TEXT("ATurret::OnDestroyReached"));
}

void ATurret::OnCrashReached()
{
	IDestructible::OnCrashReached();
	SmokeParticle->SetVisibility(true);
	UE_LOG(LogTemp, Log, TEXT("ATurret::OnCrashReached"));
}

void ATurret::OnTargetReached()
{
	IDestructible::OnTargetReached();
	UE_LOG(LogTemp, Log, TEXT("ATurret::OnTargetReached"));
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
			shot->SetTargetTag(TagStrings::EnemyShipTag);
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake, 1);
			--CurrentAmmo;
			UGameplayStatics::PlaySoundAtLocation(this, ShootSound, SpawnLocation);
			
			if (CurrentAmmo == 0) {
				IsDestroying = true;
				Release();
				OnDestroy();
			}
		}
	}
}

void ATurret::Release()
{
	if (ShootingPerson != NULL) {
		ShootingPerson->SetActorHiddenInGame(false);

		APlayerController* pc = GetWorld()->GetFirstPlayerController();
		pc->Possess(ShootingPerson);

		SetActorRotation(InitialRotation);
		ShootingPerson->SetActorLocation(CharacterPos);
		ShootingPerson = NULL;

		UE_LOG(LogTemp, Log, TEXT("Release"));
		APlayerCameraManager* cm = pc->PlayerCameraManager;
		UE_LOG(LogTemp, Log, TEXT("ViewYawMin: %d"), cm->ViewYawMin);
		UE_LOG(LogTemp, Log, TEXT("ViewYawMax: %d"), cm->ViewYawMax);
		UE_LOG(LogTemp, Log, TEXT("ViewPitchMin: %d"), cm->ViewPitchMin);
		UE_LOG(LogTemp, Log, TEXT("ViewPitchMax: %d"), cm->ViewPitchMax);

		pc->PlayerCameraManager->ViewYawMin = -360;
		pc->PlayerCameraManager->ViewYawMax = 360;
		pc->PlayerCameraManager->ViewPitchMin = -30;
		pc->PlayerCameraManager->ViewPitchMax = 90;
	}
}