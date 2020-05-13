#include "TeslaTurret.h"
#include "EnemyShip.h"

ATeslaTurret::ATeslaTurret() {
	SourcePoint = CreateDefa
}

void ATeslaTurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float seconds = GetWorld()->GetTimeSeconds();

	if (Target == nullptr) {
		if (LastCheck > seconds) {
			//FindTarget
			LastCheck = seconds + CheckRate;
		}
	}
	else {
		if(LastShot > seconds){
			Attack();
			LastShot = seconds + AttackRate;
		}
	}
}

void ATeslaTurret::Attack() {
	if (Target != nullptr) {

		/*auto particle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), LightingParticle, GetActorLocation());
		particle->SetWorldScale3D(ParticleSize);*/

	}
}