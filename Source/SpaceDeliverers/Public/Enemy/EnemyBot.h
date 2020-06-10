#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Character.h"
#include "EnemyBot.generated.h"

class UWidgetComponent;
class UParticleSystemComponent;
class IDestructible;
class ABuildingPlatform;

UCLASS()
class SPACEDELIVERERS_API AEnemyBot : public ACharacter, public IInteractive
{
	GENERATED_BODY()

public:
	AEnemyBot();
	virtual bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;
	virtual float GetInteractionTime() override { return InteractionTime; }

	UFUNCTION(BlueprintImplementableEvent, Category = "EnemyBot")
	void OnBotHit(ACharacter* character, float duration);

	UFUNCTION(BlueprintCallable)
	void OnTargetReached(AActor* destroyTarget);

	virtual void OnSelect(class UInteractionComponent* interComp) override;
	virtual void OnDeselect() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UWidgetComponent* WidgetComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	UParticleSystemComponent* SpawnParticle;

	UFUNCTION(BlueprintImplementableEvent, Category = "EnemyShip")
	void OnSpawnBP();

	inline void SetTargetPlatform(ABuildingPlatform* target) { TargetPlatform = target; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ABuildingPlatform* TargetPlatform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector ParticleSize;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float InteractionTime = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeToCrash = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float TimeToDestroy = 10;

	UPROPERTY(BlueprintReadOnly)
	bool IsDestroying = false;
	
	IDestructible* Target = nullptr;

};
