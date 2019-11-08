#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponProjectile.generated.h"

UCLASS()
class SPACEDELIVERERS_API AWeaponProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeaponProjectile();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditDefaultsOnly)
	FName TargetTag;

	UPROPERTY(EditDefaultsOnly)
	int Damage;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
