#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gem.generated.h"

UCLASS()
class SPACEDELIVERERS_API AGem : public AActor
{
	GENERATED_BODY()
	
public:	
	AGem();

	void PlaySpawnAnimation(FVector spawnLocation);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gem")
	void OnPlaySpawnAnimation(FVector spawnLocation, float x, float y);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gem")
	void OnCollect();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	float Height;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class USphereComponent* Sphere;

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly)
	float Radius;
	
};
