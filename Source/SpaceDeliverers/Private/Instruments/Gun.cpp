#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyDrill.h"

AGun::AGun() {

}

void AGun::BeginPlay()
{
}

InstrumentType AGun::GetType() const
{
	return InstrumentType::Gun;
}

void AGun::Shoot(AActor * target) const
{
	AEnemyDrill* drill = Cast<AEnemyDrill>(target);
	if (drill != NULL && ShootParticle != NULL) 
	{
		FVector location = Mesh->GetSocketLocation(SocketName);
		UParticleSystemComponent* ps = UGameplayStatics::SpawnEmitterAttached(ShootParticle, drill->GetMesh(), FName(TEXT("None")), FVector(0), FRotator(0), EAttachLocation::KeepRelativeOffset);
		ps->SetBeamTargetPoint(0, location, 0);
	}
}
