#include "Turret.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/StaticMeshComponent.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATurret::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

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
	}
}

void ATurret::Fire()
{
}

