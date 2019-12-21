#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/StaticMeshComponent.h"

AGun::AGun() {

}

void AGun::BeginPlay()
{
}

InstrumentType AGun::GetType() const
{
	return InstrumentType::Gun;
}

void AGun::Shoot(AActor * target)
{
	if (ShootParticle != NULL) {
		FVector location = Mesh->GetSocketLocation(SocketName);
		FRotator rotation = Mesh->GetSocketRotation(SocketName);
		UGameplayStatics::SpawnEmitterAttached(ShootParticle, Mesh, FName(TEXT("None")), location, rotation, EAttachLocation::KeepRelativeOffset);
	}
}
