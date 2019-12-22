#pragma once

#include "CoreMinimal.h"
#include "Instruments/Instrument.h"
#include "Gun.generated.h"

UCLASS()
class SPACEDELIVERERS_API AGun : public AInstrument
{
	GENERATED_BODY()
	
public:
	AGun();
	virtual void BeginPlay() override;
	virtual InstrumentType GetType() const override;
	void Shoot(AActor* target);

	FORCEINLINE int GetDamage() { return Damage; }

protected:
	UPROPERTY(EditDefaultsOnly)
	int Damage;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ShootParticle;

	UPROPERTY(EditDefaultsOnly)
	FName SocketName;
};