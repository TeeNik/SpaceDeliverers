#include "Turret.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;

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

