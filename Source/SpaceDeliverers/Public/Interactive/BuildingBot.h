#pragma once

#include "CoreMinimal.h"
#include "Interactive.h"
#include "GameFramework\Actor.h"
#include "BuildingBot.generated.h"

UCLASS()
class SPACEDELIVERERS_API ABuildingBot : public AActor, public IInteractive
{
	GENERATED_BODY()

public:
	ABuildingBot();

	virtual bool Interact(class UInteractionComponent* interComp, ACharacter* character) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<class ABuilder> BuilderBase;

	virtual void OnSelect(class UInteractionComponent* interComp) override;
	virtual void OnDeselect() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = EnemyShip, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* Box;
};
