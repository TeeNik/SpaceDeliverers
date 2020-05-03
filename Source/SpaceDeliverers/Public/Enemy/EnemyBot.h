#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework/Character.h"
#include "EnemyBot.generated.h"

UCLASS()
class SPACEDELIVERERS_API AEnemyBot : public ACharacter, public IInteractive
{
	GENERATED_BODY()

public:
	AEnemyBot();
	virtual bool Interact(class UInteractionComponent* interComp, class ACharacter* character) override;
	virtual float GetInteractionTime() override { return InteractionTime; }

	UFUNCTION(BlueprintImplementableEvent, Category = "EnemyDrill")
	void OnBotHit(ACharacter* character, float duration);

	virtual void OnSelect(class UInteractionComponent* interComp) override;
	virtual void OnDeselect() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FVector ParticleSize;

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	float InteractionTime = 10;

};
