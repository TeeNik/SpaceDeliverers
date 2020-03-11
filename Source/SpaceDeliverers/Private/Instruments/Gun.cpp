#include "Gun.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/StaticMeshComponent.h"
#include "EnemyBot.h"

InstrumentType AGun::GetType() const
{
	return InstrumentType::Gun;
}

void AGun::Shoot(AActor * target) const
{
	AEnemyBot* drill = Cast<AEnemyBot>(target);
	if (drill != NULL && ShootParticle != NULL) 
	{
		FVector location = Mesh->GetSocketLocation(SocketName);
		UParticleSystemComponent* ps = UGameplayStatics::SpawnEmitterAttached(ShootParticle, drill->GetMesh(), FName(TEXT("None")), FVector(0), FRotator(0), EAttachLocation::KeepRelativeOffset);
		ps->SetRelativeScale3D(FVector(.05f, .05f, .05f));
		ps->SetBeamTargetPoint(0, location, 0);
	}
}
