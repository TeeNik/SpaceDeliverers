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

#include "WeaponProjectile.h"
#include "InteractionComponent.h"
#include "Camera/CameraShake.h"
#include "Kismet/GameplayStatics.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	RootComponent = Arrow;
	Box->SetupAttachment(Arrow);
	Mesh->SetupAttachment(Arrow);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Mesh);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
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
			GetWorld()->GetFirstPlayerController()->PlayerCameraManager->PlayCameraShake(CameraShake, 1);
			--CurrentAmmo;
			UGameplayStatics::PlaySoundAtLocation(this, ShootSound, SpawnLocation);
			
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