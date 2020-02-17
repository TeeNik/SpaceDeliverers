#pragma once

#include "CoreMinimal.h"
#include "Instruments/Instrument.h"
#include "Gun.generated.h"

UCLASS()
class SPACEDELIVERERS_API AGun : public AInstrument
{
	GENERATED_BODY()
	
public:
	virtual InstrumentType GetType() const override;
	void Shoot(AActor* target) const;

	FORCEINLINE int GetDamage() const { return Damage; }

protected:
	UPROPERTY(EditDefaultsOnly)
	int Damage;

	UPROPERTY(EditDefaultsOnly)
	class UParticleSystem* ShootParticle;

	UPROPERTY(EditDefaultsOnly)
	FName SocketName;
};